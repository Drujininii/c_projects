#include <iostream>
#include <vector>
#include <cstring>

template <typename T>
void merge(T *array1, T *array2, size_t size_first, size_t size_second, T *result);

template <typename T>
void vjuh_sort(T *array1, size_t size);

template <typename T>
void merge_sort(T *array, size_t size);

void foo(char array[100][100]);

char array[100][100];
int main() {
    array[0][0] = 'c';
    foo(array);
    std::cout << array[0][0] << " " << array[0][1] << " " << array[0][2];
    size_t size;
    size_t period;
    std::cin >> size;
    std::cin >> period;
    std::vector<int> vec;
    std::vector<int> result;
    int value;
    int temp[period];
    for (size_t i = 0; i < size; i++) {
        std::cin >> value;
        vec.push_back(value);
        if (vec.size() % (period) == 0)
            merge_sort(&vec[vec.size() - period], period);//ДОДЕЛАТЬ ЧТОБЫ СОРТИРОВАЛ ТОЛЬКО К ЭЛЕМЕНТОВ А НЕ 2 К
        if (vec.size() == 2 * period) {
            merge(&vec[0], &vec[period], period, period, temp);
            for (size_t j = 0; j < period; j++) {
                std::cout << temp[i] << " ";
                vec.clear();
                vec.push_back(temp[period + j]);
                }
            }
        }
    merge_sort(&vec[0], vec.size());
    while (!vec.empty()) {
        std::cout << *vec.begin() << " ";
        vec.erase(vec.begin());
    }
    return 0;
}


template <typename T>
void merge(T *array1, T *array2, size_t size_first, size_t size_second, T *result) {
    size_t i = 0;
    size_t j = 0;
    while (size_first && size_second) {
        if (array1[i] < array2[j]) {
            *(result + i + j) = array1[i];
            i++;
            size_first--;
        }
        else {
            *(result + i + j) = array2[j];
            j++;
            size_second--;
        }
    }
    while (size_first != 0) {
        *(result + i + j) = array1[i];
        i++;
        size_first--;
    }
    while (size_second != 0) {
        *(result + i + j) = array2[j];
        j++;
        size_second--;
    }
    return;
}


template <typename T>
void merge_sort(T *array, size_t size) {
    if (size <= 1)
        return;
    size_t first_half_size = size / 2;
    size_t second_half_size = size - first_half_size;
    merge_sort(array, first_half_size);
    merge_sort(array + first_half_size, second_half_size);
    T *result = new T [size];
    merge(array, array + first_half_size, first_half_size, second_half_size, result);
    memcpy(array, result, sizeof(T) * size);
    delete [] result;
}




void foo(char array[100][100]) {
    array[0][1] = 'b';
    array[0][2] = 'd';
    std::cout << array[0][0];
}