//Аналогично 1.2, но ломаная должна быть замкнутая. Предполагается, что никакие три точки не
//
//лежат на одной прямой.
//
//Указание: стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек
//
//несколько, то используйте точку с наименьшей координатой y.
//
//Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех
//
//остальных точек.




#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <limits>



struct Point;


template <typename T, typename K>
void kostil_sort(T *array, size_t number_of_elem, std::function<bool(K &, K &)> comparator) {
    for (size_t i = 1; i < number_of_elem; i++) {
        if (comparator(*(array + i), *(array + i - 1)))
            continue;
        size_t j = i;
        while ((j != 0) && (!comparator(*(array + j) , *(array + j - 1)))) {
            std::swap(*(array + j), *(array + j - 1));
            j--;
        }
    }
}

struct Point {
    int x_coord;
    int y_coord;
    bool operator > (const Point &) const ;
    bool operator == (const Point &) const;
    bool operator < (const Point &) const;
    friend std::ostream & operator << (std::ostream &os, const Point &obj);
};

bool Point::operator > (const Point &another) const {
    if (this->x_coord > another.x_coord)
        return true;
    else if ((this->x_coord == another.x_coord) && (this->y_coord > another.y_coord))
        return true;
    return false;
}

bool Point::operator == (const Point &another) const {
    if ((this->x_coord == another.x_coord) && (this->y_coord == another.y_coord))
        return true;
    return false;
}

bool Point::operator<(const Point &another) const {
    if (this->x_coord < another.x_coord)
        return true;
    else if ((this->x_coord == another.x_coord) && (this->y_coord < another.y_coord))
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const Point &obj) {
    os << obj.x_coord << " " << obj.y_coord << std::endl;
    return os;
}




class Field {
public:
    Field() = delete;
    Field(std::vector<Point> &);
    void sort_field();
    friend std::ostream & operator << (std::ostream &os, Field &obj);
    std::vector<Point> field;
private:
    double tang(const Point &) const;//находит тангенс угла между осью y и лучом на точку
    void find_first();
};

void Field::find_first() {
    if (field.size() < 2)
        return;
    std::vector<Point>::iterator current_element = field.begin();
    while(current_element != field.end()) {
        if (*field.begin() > *current_element)
            std::iter_swap(field.begin(), current_element);
        current_element++;
    }
}

Field::Field(std::vector<Point> &vector) {
    field = vector;
    find_first();
}


std::ostream &operator << (std::ostream &os, Field &obj) {
    std::vector<Point>::iterator current_element = (obj.field.begin());
    while (current_element != obj.field.end()) {
        os << *current_element;
        current_element++;
    }
    return os;
}

//bool comparator(const Point & pt1, const Point & pt2) const{
//    if (tang(pt2) < tang(pt1))
//        return true;
//    return false;
//}

double Field::tang(const Point &pt) const{
    if (pt == field[0])
        return std::numeric_limits<double>::max();
    if (pt.x_coord == field[0].x_coord) {
        double result = std::numeric_limits<double>::max()/10;
        return result;
    }
    if (pt.y_coord == field[0].y_coord) {
        return 0;
    }
    double tg = ((double)pt.y_coord - (double)field[0].y_coord)/((double)pt.x_coord - (double)field[0].x_coord);
    return tg;
}

void Field::sort_field() {//стд фанкшион
    ::kostil_sort<Point, Point>(&field[0], field.size(), [this](Point &pt1, Point &pt2)->bool {
        return tang(pt2) > tang(pt1);
    });
}






int main() {
    std::vector<Point> vect_point;
    Point pt;
    size_t number_of_coord;
    std::cin >> number_of_coord;

    for (size_t i = 0; i < number_of_coord; i++){
        std::cin >> pt.x_coord;
        std::cin >> pt.y_coord;
        vect_point.push_back(pt);
    }
    Field obj(vect_point);
    obj.sort_field();
    std::cout << obj;
    return 0;
}

