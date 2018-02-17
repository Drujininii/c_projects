#include <iostream>
#include <vector>
#include <assert.h>

template <typename T>
T *partition(T *array, size_t size, T **pivot);

template <typename T>
T k_static_find(T *array, size_t size, size_t k_static_number);


int main() {
    size_t size;
    size_t k_static_number;
    std::cin >> size;
    std::cin >> k_static_number;
    std::vector<int> vec;
    vec.reserve(size);
    int value;
    for (size_t i = 0; i < size; i++) {
        std::cin >> value;
        vec.push_back(value);
        }
    int result = k_static_find(&vec[0], vec.size(), k_static_number);
    std::cout << result << std::endl;
    return 0;
}




template <typename T>
T k_static_find(T *array, size_t size, size_t k_static_number) {
    T *pivot;
    while (1) {
        pivot = array + rand() % size;
        pivot = partition(array, size, &pivot);
        if (pivot - array > k_static_number) {
            size = pivot - array;
            continue;
        }
        else if (pivot - array < k_static_number) {
            size = array + size - 1 - pivot;
            k_static_number = k_static_number - (pivot - array + 1);
            array = pivot + 1;
            continue;
        }
        else if (pivot - array == k_static_number)
            break;
        else
            assert(0);
    }
    return *pivot;
}



template <typename T>
T *partition(T *array, size_t size, T **pivot) {
    size_t j = size;
    size_t i = j;
    std::swap(array[0], **pivot);
    *pivot = array;
    while (j != 0) {
        if (array[j - 1] < **pivot)
            j--;
        else {
            std::swap(array[i - 1], array[j - 1]);
            j--;
            i--;
        }
    }
    return array + i;
}