//Дан массив целых чисел A[0..n). Массив произвольным образом заполнен натуральными числами из
//диапазона [0..n - 1). Одно или несколько значений в массиве может повторяться. Необходимо найти любой
//повтор за O(n), памяти O(1). Исходный массив хранить можно, модифицировать нельзя.
//n ≤ 10000.

#include <iostream>
#include <cassert>
#include <cmath>

template <class T>
class My_vector {
public:
    My_vector();
    My_vector(size_t);
    My_vector(const My_vector &); //copy constructor
    ~My_vector();

    void set_elem(T, size_t);
    void add_elem(T, size_t, size_t);

    void push_back(T);
    void push_front(T);
    T pop(size_t);
    void delete_element(size_t);


    size_t vector_size();

    My_vector &operator=(My_vector &);
    T &operator[](size_t);
//    bool operator>(My_vector &);



private:
    void resize();
    size_t size;
    size_t capacity;
    T *array;
};




template <class T>
My_vector<T>::My_vector() {
    size = 0;
    capacity = 1024;
    try {
        array = new T[capacity];
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
My_vector<T>::My_vector(const My_vector<T> &another) {
    size = another.size;
    capacity = another.capacity;
    try {
        array = new T(capacity);
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    for(size_t i = 0; i < another.size; i++)
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
        temp = new T[capacity];
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
T &My_vector<T>::operator[](size_t number_element) {
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

template <class T>
void My_vector<T>::set_elem(T elem, size_t number) {
    *(array + number) = elem;
}

template <class T>
void My_vector<T>::push_front(T insert) {
    T temp;
    for (size_t i = 0; i < vector_size(); i++) {
        temp = this[i];
        set_elem(i, insert);
        insert = temp;
    }
    push_back(temp);
}

template <class T>
void My_vector<T>::add_elem(T insert, size_t number, size_t number_replacing_el) {
    T temp;
    for (size_t i = number; i < number_replacing_el; i++) {
        temp = *(array + i);
        set_elem(insert, i);
        insert = temp;
    }
    set_elem(insert, number_replacing_el);
}




class Find_Repeat_Number {
public:
private:
};


My_vector<int> &find_repeated_number(int *pInt, size_t);

int main() {
    size_t number_of_number;
    std::cin >> number_of_number;
    int *array_value = new int [number_of_number];

    std::cout << "number = " << number_of_number << ' ';

    for (size_t i = 0; i < number_of_number; i++) {
        std::cin >> *(array_value + i);
    }

    find_repeated_number(array_value, number_of_number);

    delete [] array_value;
    return 0;
}

My_vector<int> &find_repeated_number(int *array, size_t size) {
    My_vector<int> repeat_number;
    unsigned long long int *bit_field = new unsigned long long int [(size - 1)/60 + 1];//чтобы в один инт влезало 500 чисел
    int k = 0;
    unsigned long long bit_set = 0;
    for (size_t i = 0; i < (size - 1)/60 + 1; i++) {
        *(bit_field + i) &= (unsigned long long int) 0;
    }
    for (size_t j = 0; j < size; j++) {
        k = array[j] / 60;//смотрим в какой инт положили число. 0-59 1-й 60-999 2-й 1000-1499 3-й и т.д.
        bit_set = (unsigned long long int) pow(2, array[j]);
        if (*(bit_field + k) & bit_set)
            repeat_number.push_back(k * 60 + array[j]);
        else
            *(bit_field + k) |= bit_set;
    }
    delete [] bit_field;
    for (size_t i = 0; i < repeat_number.vector_size(); i++)
        std::cout << repeat_number[i] << " ";
    return repeat_number;
}