//​Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти первую пару
//индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}. Время работы -
//O(n).
//n ≤ 100000.

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <limits>
#include <cstdlib>
//template <class T> class My_vector;
//template <char> std::istream &operator>>(std::istream &, My_vector<char> &);

struct key_value {
    size_t number;
    int value;
};

//структура для хранения индексов элементов с максимальной суммой
struct key_key {
    size_t idx1;
    size_t idx2;
};

template <class T>
class My_vector {
public:
    My_vector();
    My_vector(size_t);
    My_vector(const My_vector &); //copy constructor
    ~My_vector();

    void push_back(T);
    T pop(size_t);
    void delete_element(size_t);

    size_t vector_size();

    T *operator*();
    template <class k> friend std::istream &operator>>(std::istream &, My_vector<k> &);

    My_vector & operator=(My_vector &);
    T operator[](size_t);
private:
    void resize();
    size_t size;
    size_t capacity;
    T *array;
};

class Find_index {
public:
    void find_idx_max_sum();
    void read();
    void print_idx();
private:
    void delete_less_than_after();
    void delete_less_than_previous();
    size_t size_of_compare_vector;
    My_vector <key_value> first;//первый подаваемый в условии массив
    My_vector <key_value> second;//второй подаваемый в условии массив
    key_key idxs;//индексы максимальных сумм
};


//удаляет значения во втором векторе, которые меньше, чем последующие
void Find_index::delete_less_than_after() {
    key_value max_temp = second[second.vector_size() - 1];
    for (size_t i = (second.vector_size() - 1); i > 0; i--) {
        if(second[i - 1].value < max_temp.value) {
            (*second + i - 1)->value = max_temp.value;//вместо элементов меньших предыдущего максимального записываем предыдущий максимальный элемент
            (*second + i - 1)->number = max_temp.number;
        }
        else {
            max_temp.value = (*second + i - 1)->value;
            max_temp.number = (*second + i - 1)->number;
        }
    }
}


//удаляет значения в первом векторе, которые меньше, чем предыдущие
void Find_index::delete_less_than_previous() {
    key_value max_temp = first[0];
    for (size_t i = 1; i < (first.vector_size()); ++i) {
        if(first[i].value <= max_temp.value) {
            (*first + i)->value = max_temp.value;//вместо элементов равных либо меньших максимального записываем максимальный элемент*
            (*first + i)->number = max_temp.number;
        }
        else {
            max_temp.value = (*first + i)->value;
            max_temp.number = (*first + i)->number;
        }
    }
}
//*позволит нам просто сложить два вектора и полученное максимальное значение будет максимальным для данных индексов
//нахождение индексов максимальной суммы
void Find_index::find_idx_max_sum() {
    delete_less_than_after();
    delete_less_than_previous();
    int max_sum = first[0].value + second[0].value;
    idxs.idx1 = first[0].number;
    idxs.idx2 = second[0].number;
    for(size_t i = 1; i < size_of_compare_vector; i++){
        if((first[i].value + second[i].value) > max_sum) {
            max_sum = first[i].value + second[i].value;
            idxs.idx1 = first[i].number;//запись индексов максимальной суммы
            idxs.idx2 = second[i].number;
        }
    }
}


void Find_index::print_idx() {
    std::cout << idxs.idx1 << " " << idxs.idx2;
}

void Find_index::read() {
//    std::cout << "Напишите размерность векторов:" << std::endl;
    std::cin >> size_of_compare_vector;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    My_vector <char> temp_value;
    key_value temp_key_value;
//    char temp = 0;
//    while(temp != '\n') {
//        temp = getchar();
//        temp_value.push_back(temp);
//    }

//Ввод первого вектора
    for(size_t i = 0; i < size_of_compare_vector; i++) {
        std::cin >> temp_key_value.value;
        temp_key_value.number = i;
        first.push_back(temp_key_value);
    }

//Ввод второго вектора
    for(size_t i = 0; i < size_of_compare_vector; i++) {
        std::cin >> temp_key_value.value;
        temp_key_value.number = i;
        second.push_back(temp_key_value);
    }
//    for(size_t i = 0; i < size_of_compare_vector; i++) {
//        temp_key_value.value = (int) strtol(ptr_space, &ptr_space, 10);
//        temp_key_value.number = i;
//        second.push_back(temp_key_value);
//    }
}


template <class T>
My_vector<T>::My_vector() {
    size = 0;
    capacity = 1024;
    try {
        array = new T[capacity];//олтловить исключение
    }
    catch(std::bad_alloc) {
        throw 1;
    }
}

template <class T>
My_vector<T>::My_vector(size_t known_size) {
    size = 0;
    capacity = known_size;
    try {
        array = new T[capacity];
    }
    catch(std::bad_alloc) {
            throw 1;
    }
}

template <class T>
My_vector<T>::My_vector(const My_vector &another) {
    size = another.size;
    capacity = another.capacity;
    try {
        array = new T(capacity);//отловить исключение
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    for(size_t i = 0; i < size; i++)
        *(array + i) = *(another.array + i);
}

template <class T>
My_vector<T>::~My_vector() {
    delete[] array;
}

template <class T>
void My_vector<T>::push_back(T new_element) {
    if(size == capacity)
        resize();
    *(array + size) = new_element;
    size++;
}

template <class T>
T My_vector<T>::pop(size_t number_element) {
    assert(number_element < size);
    return *(array + number_element);
}

template <class T>
size_t My_vector<T>::vector_size() {
    return size;
}

template <class T>
void My_vector<T>::resize() {
    capacity *= 2;
    T *temp;
    try {
        temp = new T[capacity];//отловить исключение
    }
    catch(std::bad_alloc) {
        throw 1;
    }
        for (size_t i = 0; i < size; i++) {
            *(temp + i) = *(array + i);
        }
        delete[] array;
        array = temp;
}

template <class T>
T My_vector<T>::operator[](size_t number_element) {
    assert(number_element < size);
    return *(array + number_element);
}

template <class T>
My_vector<T> &My_vector<T>::operator=(My_vector &vector) {
    if(this != &vector) {
        size = vector.size;
        capacity = vector.capacity;
        delete[] array;
        try {
            array = new T[capacity];
        }
        catch(std::bad_alloc) {
            throw 1;
        }
        for (size_t i = 0; i < size; ++i) {
            *(array + size) = *(vector.array + size);
        }
    }
    return *this;
}

template <class T>
void My_vector<T>::delete_element(size_t number_to_delete) {//удаляет элемент по номеру. нумерация с нуля до size - 1
    assert(number_to_delete < size);
    for(size_t i = 0; i < (size - number_to_delete - 1); i++) {//можно обойтись одной переменной, но потеряется смысл
        *(array + number_to_delete + i) = *(array + number_to_delete + i + 1);
    }
    size--;
}

template <class T>//жесть с перезаписью. а че б и нет. главное чтоб работало. Не используется в программе
std::istream &operator>>(std::istream &is, My_vector<T> &vector) {
    char temp = 0;
    while(temp != '\n') {
        std::cin.get(&temp, 1, '\n');
        vector.push_back(temp);
    }
    return is;
}

template <class T>//вроде тоже перестал использовать. костыль для вектора char
T *My_vector<T>::operator*() {
    return array;
}


int main() {
    Find_index object1;
    try {
        object1.read();
    }
    catch(int i) {
        std::cout << "Ошибка № " << i << std::endl;
        return 0;
    }
    object1.find_idx_max_sum();
    object1.print_idx();
//    std::cout <<  std::endl << EOF << " мусор, немного мусора, еще немного мусора" << std::endl;
//    std::cout << "ХА-ХА-ХА!" << std::endl;
    return 0;
}


