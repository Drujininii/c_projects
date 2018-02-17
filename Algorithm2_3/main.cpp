#include <iostream>
#include <limits>
#include <vector>

struct Paint_Row;

template <typename T>
T *heap_init_sort(T *array, size_t size);

template <typename T>
T *pir_sort(T *array, size_t size);

template <typename T>
T &pop_max(T *array, size_t number_elems);

template <typename T>
T &erase_elem(T *array, size_t number_elem, size_t number_elems);

size_t count_colored_row(std::vector<Paint_Row> &vec);

struct Paint_Row {
    size_t begin;
    size_t end;
    bool operator > (const Paint_Row &) const ;
    bool operator == (const Paint_Row &) const;
    bool operator < (const Paint_Row &) const;
    friend std::ostream & operator << (std::ostream &os, const Paint_Row &obj);
};

bool Paint_Row::operator > (const Paint_Row &another) const {
    if (this->begin > another.begin)
        return true;
    else if ((this->begin == another.begin) && (this->end > another.end))
        return true;
    return false;
}

bool Paint_Row::operator == (const Paint_Row &another) const {
    return (this->begin == another.begin) && (this->end == another.end);
}

bool Paint_Row::operator < (const Paint_Row &another) const {
    if (this->begin < another.begin)
        return true;
    else if ((this->begin == another.begin) && (this->end < another.end))
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const Paint_Row &obj) {
    os << obj.begin << " " << obj.end << std::endl;
    return os;
}






int main() {
    Paint_Row row;
    std::vector<Paint_Row> straight_paint;
    size_t number;
    std::cin >> number;

//    std::vector<size_t> test_vec;
//    size_t data;
//    for (size_t i = 0; i < number; i++) {
//        std::cin >> data;
//        test_vec.push_back(data);
//    }
//
//    pir_sort(&test_vec[0], test_vec.size());
//    for (size_t i = 0; i < number; i++)
//        std::cout << test_vec[i] << std::endl;


    for (size_t i = 0; i < number; i++) {
        std::cin >> row.begin;
        std::cin >> row.end;
        straight_paint.push_back(row);
    }
    pir_sort(&straight_paint[0], straight_paint.size());
//    for (size_t i = 0; i < number; i++) {
//        std::cout << straight_paint[i];
//    }
    std::cout << count_colored_row(straight_paint);
    return 0;
}






template <typename T>
T *pir_sort(T *array, size_t size) {
    heap_init_sort(array, size);
    for (size_t i = size; i >= 1; i--) {
        pop_max(array, i);//нет возвращаемого значения, т.к. все элементы остаются в конце массива
    }
    return array;
}

template <typename T>
T *heap_init_sort(T *array, size_t size) {
    for (size_t i  = (size - 2) / 2; i < std::numeric_limits<size_t>::max(); i--) //цикл для верхней половины элементов т.к. size t беззнаковый
        for (size_t j = i; j <= (size - 2) / 2; ) { //
            size_t k = j * 2 + 1;
            if ((k + 1) < (size) && array[k] < array[k + 1]) {
                k++;
            }
            if (*(array + j) < *(array + k)) {
                std::swap(array[j], array[k]);
                j = k;
            }
            else
                break;
        }
    return array;
}

template <typename T>
T &erase_elem(T *array, size_t number_elem, size_t number_elems) {
    std::swap(array[number_elem], array[number_elems - 1]);
    for (size_t i = number_elem; (2 * i + 1) < (number_elems - 1);) {
        i = (i * 2) + 1;
        if ((i + 1) < (number_elems - 1) && array[i] < array[i + 1])
            i++;
        if (array[(i - 1) / 2] < array[i])
            std::swap(array[(i - 1) / 2], array[i]);
        else
            break;
    }
    return array[number_elems - 1];
}



template<typename T>
T &pop_max(T *array, size_t number_elems) {
    return erase_elem(array, 0, number_elems);
}

size_t count_colored_row(std::vector<Paint_Row> &vec) {
    size_t length = 0;
    for (size_t i = 0; i < (vec.size() - 1); i++) {
        if (vec[i].end > vec[i + 1].begin)
            length += vec[i + 1].begin - vec[i].begin;
        else
            length += vec[i].end - vec[i].begin;

        if (vec[i].end > vec[i + 1].end) {
            vec[i + 1].begin = vec[i + 1].end;
            vec[i + 1].end = vec[i].end;
        }
        else {
            if (vec[i + 1].begin < vec[i].end)
                vec[i + 1].begin = vec[i].end;
        }
    }
    length += (vec[vec.size() - 1].end - vec[vec.size() - 1].begin);//для последнего элемента
    return length;
}