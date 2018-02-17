//нулевое направление градиента - горизонталь
//применить ГАуссову фильтрацию пикселей на краю блока перед накоплением значений в ячейках. эт где?
//подумать над перекрытие блоков
//вытащить выделение памяти в самое начало. вынуть в normalization (и в остальных местах) все лишнии расчеты за пределы цикла
//перейти везде к инт
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>


#define PI 3.14159265
#define WIDTH_FRAME_HOG 8
#define WIDTH_BLOCK_HOG 1
#define HEIGHT_BLOCK_HOG WIDTH_BLOCK_HOG;
#define INPUT_IMAGE "./image0.jpg"


void vote_nearest_angles(cv::Vec2i& pixel_HOG_data, std::map<int, int>& histogram, std::vector<int>& correct_angle);

void convert_to_HOG(cv::Mat_<cv::Vec2i>& Roi_, cv::Mat& Cell_HOG_, std::vector<int>& correct_angle);

void draw_square_H0G(cv::Mat& Cell_HOG, cv::Mat_<uchar> &Cell_HOG_draw);

void normalization(cv::Mat& Cells_HOG_matrix,  std::vector<cv::Mat>& result_HOG_vector);


int count_block_norm_value(cv::Mat& mat);

using std::cin;
using std::cout;
using std::endl;

int angle_step = 20;



int main() {
    cv::namedWindow("Image Box", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("FULL HOG", CV_WINDOW_AUTOSIZE);

    cv::VideoCapture capture(CV_CAP_ANY);
    while (true) {

//        const std::string image_name = INPUT_IMAGE;
        cv::Mat image;
        if (!capture.read(image))
            break;
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, CV_BGR2GRAY);
//        image = cv::imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
        if (image.empty()) {
            return -1;
        }

        cv::Mat image_with_border(image.rows + 2, image.cols + 2, CV_8UC1);
        cv::Rect border(1, 1, image.cols, image.rows);
        image.copyTo(image_with_border(border));
        cv::Mat_<uchar> image_with_border_ = image_with_border;//заменим имаж_ на имаж _виф_бордер
        //вычисление градиента пикселя
        //задание направлений градиента хога
        int x_diff = 0;
        int y_diff = 0;
        int number_of_correct_angle = 10;
        std::vector<int> correct_angle;
        int angle = 0;
        double angle_offset_factor = -4.5;
        //так как нулевой угол - горизонталь, то отклонение угла вверх - это -, а вниз - +. начальный угол отсчета -90
        for (int i = 0; i < number_of_correct_angle; i++) {
            angle = (int) (angle_step * (i + angle_offset_factor));
            correct_angle.push_back(angle);
        }
        //корректные углы: -90, -70, -50, -30, -10, 10, 30, 50, 70, 90
        cv::Mat_<cv::Vec2i> Pixel_HOG_Array_(image.rows, image.cols);

        cv::Vec2i temp_pixel_data;
        int calculated_angle = 0;
        for (size_t i = 1; i < image_with_border_.rows - 1; i++) {
            for (size_t j = 1; j < image_with_border_.cols - 1; j++) {
                x_diff = (image_with_border_(i, j + 1) - image_with_border_(i, j - 1));
                y_diff = (image_with_border_(i - 1, j) - image_with_border_(i + 1, j));

                temp_pixel_data[1] = (int) sqrt(x_diff * x_diff + y_diff * y_diff);

                if (x_diff != 0)
                    calculated_angle = (int) (atan(y_diff / x_diff) * 180 / PI);
                else
                    calculated_angle = -90;
                temp_pixel_data[0] = calculated_angle;
                Pixel_HOG_Array_.at<cv::Vec2i>(i - 1, j - 1) = temp_pixel_data;
            }
//        gaus_smooth_pixel_hog_array(Pixel_HOG_Array_);надо сделать гауссовое размытие крайних пикселей
        }

        //вычисление ячейки
        size_t width_frame_HOG = WIDTH_FRAME_HOG;
        int x_number_cells = image.cols / width_frame_HOG;
        int y_number_cells = image.rows / width_frame_HOG;
        cv::Mat_<uchar> Cells_Hog_draw(image.rows, image.cols, (uchar) 0);
        const int size_of_HOG_cells_mat[] = {y_number_cells, x_number_cells, 9};

        std::vector<cv::Mat> Cells_HOG_vector;
        Cells_HOG_vector.reserve((unsigned int) y_number_cells * x_number_cells);

        cv::Mat_<uchar> Cell_Hog_uchar(width_frame_HOG, width_frame_HOG, (uchar) 0);

        cv::Mat_<cv::Vec2i> Roi_(width_frame_HOG, width_frame_HOG);

        cv::Size size_frame_HOG = cv::Size(width_frame_HOG, width_frame_HOG);
        cv::Point offset_frame_HOG(0, 0);

        cv::Mat matrix(3, size_of_HOG_cells_mat, CV_32SC2, cv::Scalar(0));



        //делает ячейки хог, а затем массив ячеек
        //можно выкинуть матрицу углов. оставить только матрицу длин векторов
        for (size_t i = 0; i < y_number_cells; i++) {
            for (size_t j = 0; j < x_number_cells; j++) {
                offset_frame_HOG.x = width_frame_HOG * j;
                offset_frame_HOG.y = width_frame_HOG * i;
                cv::Rect frame_HOG(offset_frame_HOG, size_frame_HOG);
                Pixel_HOG_Array_(frame_HOG).copyTo(Roi_);//вырезаем рамку под хог 16х16
                cv::Mat cell = matrix.row(i).col(j);

                //конвертирование квадратиков в хог
                convert_to_HOG(Roi_, cell, correct_angle);//создает одну ячейку
            }
        }


        std::vector<cv::Mat> result_HOG_vector;
        normalization(matrix, result_HOG_vector);


        size_t cell_curr_number = 0;
        for (size_t i = 0; i < y_number_cells; i++) {
            for (size_t j = 0; j < x_number_cells; j++) {
                offset_frame_HOG.x = width_frame_HOG * j;
                offset_frame_HOG.y = width_frame_HOG * i;
                cv::Rect frame_HOG(offset_frame_HOG, size_frame_HOG);
                cv::Mat cell = matrix.row(i).col(j);
                draw_square_H0G(cell, Cell_Hog_uchar);//передаем нужный нам участок (ячейку) для рисования хога
                Cells_Hog_draw(frame_HOG) += Cell_Hog_uchar;
                cell_curr_number++;
            }
        }

//        cv::Point offset_find_window(250, 210);
//        cv::Size size_window_find = cv::Size(192, 192);
//        cv::Rect window_scan(offset_find_window, size_window_find);
//        cv::Mat window_scan_mat;
//        Cells_Hog_draw(window_scan).copyTo(window_scan_mat);
//        imshow("Window_Scan", window_scan_mat);


//        std::vector<int> compression_params;
//        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//        compression_params.push_back(100);
//    cv::imwrite("image_with_norm.jpg", Cells_Hog_draw);
        imshow("Image Box", image);
        imshow("FULL HOG", Cells_Hog_draw);
        const char c = (char) cvWaitKey(1);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }
    cv::destroyAllWindows();
    return 0;
}











void vote_nearest_angles(cv::Vec2i& pixel_HOG_data, std::map<int, int>& histogram, std::vector<int>& correct_angle) {
    size_t gap = 0;
    size_t left_border = 0;
    size_t right_border = correct_angle.size() - 1;

    double scale_factor; //взвешивает значения пикселя относительно двух ближайших углов.
    // то есть если значение угла пикселя находятся между разрешенный углов
    while (left_border != right_border - 1) {
        gap = (left_border + right_border)/2;
        if (pixel_HOG_data[0] < correct_angle[gap])
            right_border = gap;
        else //(pixel_HOG_data[0] > correct_angle[gap])
            left_border = gap;
    }
    //устраняем неоднозначность в указатели на элемент т.к. элемент может быть либо ближе к gap либо gap +-1
    scale_factor = abs(correct_angle[left_border] - pixel_HOG_data[0]) / angle_step;
    histogram[correct_angle[left_border]] += (int) (pixel_HOG_data[1] * (1 - scale_factor));//значения пикселя распределяется между углами
    histogram[correct_angle[right_border]] += (int) (pixel_HOG_data[1] * scale_factor);
    return;
}





void convert_to_HOG(cv::Mat_<cv::Vec2i>& Roi_, cv::Mat& Cell_HOG_, std::vector<int>& correct_angle) {
    //c учетом исключения направления на 90 градусов
    std::map<int, int> histogram;

    //создаем мап из углов и значений градиента по этим направлениям
    for (size_t i = 0; i < correct_angle.size(); i++)
        histogram.insert(std::make_pair(correct_angle[i], 0));

    //создаем гисторграмму ячейки
    int angle_step = 20;
    for (size_t i = 0; i < Roi_.rows; i++) {
        for (size_t j = 0; j < Roi_.cols; j++) {
            if ((Roi_(i, j)[0] - 10) % angle_step != 0)
                vote_nearest_angles(Roi_(i, j), histogram, correct_angle);
            else {
                histogram[Roi_(i, j)[0]] += Roi_(i, j)[1];
            }
        }
    }
    histogram.find(-90)->second += histogram.find(90)->second;//убрали значение +90 градусов!!!!
    std::map<int, int>::iterator histogram_iter = histogram.begin();
    for (size_t i = 0; i < correct_angle.size() - 1; i++) {
        Cell_HOG_.at<cv::Vec2i>(i)[0] = histogram_iter->first;//заполняем значение каждой точки диаграммы
        Cell_HOG_.at<cv::Vec2i>(i)[1] = histogram_iter->second;
        histogram_iter++;
    }
}



void draw_square_H0G(cv::Mat& Cell_HOG, cv::Mat_<uchar> &Cell_HOG_draw_) {
    //rows -  количество углов. т.е. Cells[i] - номер нужной ориентации.
    //Cells[i][0] - значение угла (в градусах)
    //Cells[i][1] - интенсивность точек в этой ориентации
    //  double normalization_value = 255/Cell_HOG_draw_.total();
    int normalization_value = 1;

    cv::Point line_point1;
    cv::Point line_point2;
    int cols = Cell_HOG_draw_.cols;
    int rows = Cell_HOG_draw_.rows;
    int delta_x = 0;
    int delta_y = 0;

    int offset = 2;
    for (size_t i = 0; i < Cell_HOG.total(); i++) {
        if (Cell_HOG.at<cv::Vec2i>(i)[0] < -45 ) {
            delta_x = (int) tan(20 * i * PI / 180.0) * (rows)/2 - offset;//т.к. тангенс, то дельта меняет знак при переходе через 90 градусов
            line_point1.x = (cols - 1) / 2 + delta_x;//нет rows - 1 т.к. это его длина
            line_point1.y = offset;
            line_point2.x = (cols - 1) / 2 - delta_x;
            line_point2.y = rows - 1 - offset;
        }
        else if (Cell_HOG.at<cv::Vec2i>(i)[0] > 45) {
            delta_x = (int) tan(20 * i * PI / 180.0) * (rows)/2 + offset;
            line_point1.x = (cols - 1) / 2 - delta_x;//т.к. дельта отрицательная
            line_point1.y = rows - 1 - offset;
            line_point2.x = (cols - 1) / 2 + delta_x;
            line_point2.y = offset;
        }
        else {
            delta_y = (int) (1/(tan(20 * i * PI / 180.0))) * (cols) / 2 - offset;
            line_point1.x = cols - 1 - offset;
            line_point1.y = (rows - 1)/2 - delta_y;
            line_point2.x = offset;
            line_point2.y = (rows - 1)/2 + delta_y;
        }
        cv::Scalar_<uchar> line_color{(uchar)(Cell_HOG.at<cv::Vec2i>(i)[1]/normalization_value)};
        cv::line(Cell_HOG_draw_, line_point1, line_point2, line_color, 1);
    }
    return;
}



//нормирует значения вектора в блоке, т.к. при суммировании в ячейки, значения получаются больше 255
//значение каждой ячейке делятся на длину вектора(блока), который состоит из 4-ч ячеек.
//нормируется значение только добавленные в вектор. значения матрицы ен меняются
void normalization(cv::Mat& Cells_HOG_matrix, std::vector<cv::Mat>& result_HOG_vector) {//количество строк в матрице ячеек
    size_t height_block_hog = HEIGHT_BLOCK_HOG;
    size_t width_block_hog = WIDTH_BLOCK_HOG;
    size_t number_of_rows = (size_t)Cells_HOG_matrix.size().height;
    size_t number_of_cols = (size_t)Cells_HOG_matrix.size().width;
    cv::Point offset_block(0, 0);

    int norm_value;

    cv::Mat Norm_Cells_Mat_length;
    std::vector<cv::Mat> channels;

    cv::split(Cells_HOG_matrix, channels);
    Norm_Cells_Mat_length = channels[1];

    for (size_t i = 0; i < number_of_rows - 1; i++) {//проходимся по всем блокам
        for (size_t j = 0; j < number_of_cols - 1; j++) {
            offset_block.x = j;
            offset_block.y = i;
            cv::Range rows_range(offset_block.y, offset_block.y + height_block_hog);
            cv::Range cols_range(offset_block.x, offset_block.x + width_block_hog);
            cv::Mat Roi = Norm_Cells_Mat_length(rows_range,
                                         cols_range);
            norm_value = count_block_norm_value(Roi);
            cv::Mat norm_HOG_block;
            Roi.copyTo(norm_HOG_block);
            if (norm_value != 0) {
                norm_HOG_block *= 255;
                norm_HOG_block /= norm_value;
            }
            else {
                norm_HOG_block.zeros(cv::Size(norm_HOG_block.cols, norm_HOG_block.rows), norm_HOG_block.type());
            }
            result_HOG_vector.push_back(norm_HOG_block);
        }
    }
    cv::merge(channels, Cells_HOG_matrix);
    return;
}


//считает и нормирует значения блока
int count_block_norm_value(cv::Mat& Block_HOG_Mat) {
    int width_vector_cell = 0;
    int one_pixel_length = 0;
    int normalization_value = 0;
    int ebs_sq = 8; //ebs квадрат(некоторая константа)
    //считаем длину блока вектора
    for (size_t i = 0; i < Block_HOG_Mat.size().height; i++)
        for (size_t j = 0; j < Block_HOG_Mat.size().width; j++) {
            width_vector_cell = 0;
            for (size_t k = 0; k < Block_HOG_Mat.row(i).col(j).total(); k++) {
                //считаем длину вектора одной ячейки
                one_pixel_length = Block_HOG_Mat.row(i).col(j).at<int>(k);
                width_vector_cell = width_vector_cell + (one_pixel_length * one_pixel_length);
            }
            normalization_value += width_vector_cell;
//            temp_value = cv::sum(Block_HOG_Mat.row(i).col(j).at<double>(k))[0];//в нулевом канале лежат данные. первый - нули
        }

    normalization_value = (int) (sqrt(normalization_value + ebs_sq) + 1);

    return normalization_value;
}
