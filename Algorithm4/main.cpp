#include <iostream>
#include <cassert>
#include <cstddef>


struct Command_Value {
    int command;
    int value;
};


template <class T>
class My_deq {
public:
    My_deq();
    My_deq(size_t);
    My_deq(const My_deq &); //copy constructor
    ~My_deq();

    void push_back(T);
    void push_front(T);
    T pop_back();
    T pop_front();
    void delete_element(size_t);
    void comparison(Command_Value);

    size_t vector_size();
    int status;
    My_deq & operator=(My_deq &);
    T operator[](size_t);
private:
    void resize();
    size_t size;
    size_t capacity;
    T *array;
    T *head;
    T *tail;
};


template <class T>
My_deq<T>::My_deq() {
    status = 0;
    size = 0;
    capacity = 1037;
    try {
        array = new T[capacity];
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    head = array;
    tail = array + capacity - 1;
}

template <class T>
My_deq<T>::My_deq(size_t known_size) {
    size = 0;
    capacity = known_size;
    try {
        array = new T[capacity];
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    head = array;
    tail = array + capacity - 1;
}

//template <class T>
//My_deq<T>::My_deq(const My_deq &another) {
//    size = another.size;
//    capacity = another.capacity;
//    try {
//        array = new T(capacity);
//    }
//    catch(std::bad_alloc) {
//        throw 1;
//    }
//    for(size_t i = 0; i < size; i++)
//        *(array + i) = *(another.array + i);
//}

template <class T>
My_deq<T>::~My_deq() {
    delete[] array;
}

template <class T>
void My_deq<T>::push_back(T new_element) {
    if(size == capacity - 1)
        resize();
    if (head == (array + capacity - 1)) {
        *head = new_element;
        head = array;
        size++;
        return;
    }
    *head = new_element;
    head++;
    size++;
}

template <class T>
void My_deq<T>::push_front(T new_element) {
    if(size == capacity - 1)
        resize();
    if (tail == array) {
        *tail = new_element;
        tail = array + capacity - 1;
        size++;
        return;
    }
    *tail = new_element;
    tail--;
    size++;
}


template <class T>
T My_deq<T>::pop_back() {
    if (size == 0) {
        return -1;
    }
    if (head == array) {
        head = array + capacity - 1;
        size--;
        return *head;
    }
    head--;
    size--;
    return *head;
}

template <class T>
T My_deq<T>::pop_front() {
    if (size == 0) {
        return -1;
    }
    if (tail == (array + capacity - 1)) {
        tail = array;
        size--;
        return *tail;
    }
    tail++;
    size--;
    return *tail;
}



template <class T>
size_t My_deq<T>::vector_size() {
    return size;
}

template <class T>
void My_deq<T>::resize() {
    this->capacity *= 2;
//    std::cout << "resize";
    assert(tail == head);


//    std::cout << "Массив до ресайз" << std::endl;
//    for (size_t i = 0; i < (capacity/2); i++)
//        std::cout << array[i] << " ";
//    std::cout << "tail: " << *tail << " " << "head: " << *head << std::endl;
//    std::cout<< std::endl;
    T *temp;
    try {
        temp = new T[capacity];
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    size_t  begin_tail = tail - array;

        for (size_t i = 0; i < (capacity - begin_tail - 1); i++) {
            *(temp + i) = *(array + begin_tail + i + 1);
        }

        for (size_t i = 0; i < begin_tail; i++) {
            *(temp + i + capacity/2 - begin_tail - 1) = *(array + i);
        }

    this->head = temp + capacity/2  - 1;

    this->tail = temp + capacity - 1;

    delete[] array;
    this->array = temp;
//    std::cout << "capacity: " << capacity << std::endl;
//    std::cout << "Массив после ресайз: "<< std::endl;
//    for (size_t i = 0; i < (capacity/2 - 1); i++)
//    std::cout << array[i] << " ";
//    std::cout << std::endl;
//    std::cout << *tail << " " << *head;
}

template <class T>
T My_deq<T>::operator[](size_t number_element) {
    assert(number_element < size);
    return *(array + number_element);
}

//template <class T>
//My_deq<T> &My_deq<T>::operator=(My_deq &vector) {
//    if(this != &vector) {
//        size = vector.size;
//        capacity = vector.capacity;
//        delete[] array;
//        try {
//            array = new T[capacity];
//        }
//        catch(std::bad_alloc) {
//            throw 1;
//        }
//        for (size_t i = 0; i < size; ++i) {
//            *(array + size) = *(vector.array + size);
//        }
//    }
//    return *this;
//}

template <class T>
void My_deq<T>::delete_element(size_t number_to_delete) {//удаляет элемент по номеру. нумерация с нуля до size - 1
    assert(number_to_delete < size);
    for (size_t i = 0; i < (size - number_to_delete - 1); i++) {//можно обойтись одной переменной, но потеряется смысл
        *(array + number_to_delete + i) = *(array + number_to_delete + i + 1);
    }
    size--;
}


template <class T>
void My_deq<T>::comparison(Command_Value data) {
    if (data.command == 1) {
        push_front(data.value);
        return;
    }
    if (data.command == 3) {
        push_back(data.value);
        return;
    }
    if (data.command == 2) {
        if (data.value != pop_front())
            status = -1;
        if (size == 0) {
            head = array;
            tail = (array + capacity - 1);
        }
        return;
    }
    if (data.command == 4) {
        if (data.value != pop_back())
            status = -1;
        if (size == 0) {
            head = array;
            tail = (array + capacity - 1);
        }
        return;
    }
}


int main() {

    Command_Value obj_c_v_1;
    unsigned int number_command;
    std::cin >> number_command;
    My_deq<unsigned int> obj_1((size_t)(number_command + 20));
    int command = 0;
    int value = 0;
    for(size_t i = 0; i < number_command; i++) {
        std::cin >> obj_c_v_1.command;
        std::cin >> obj_c_v_1.value;
        obj_1.comparison(obj_c_v_1);
        if (obj_1.status == -1) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}


