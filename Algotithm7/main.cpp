//7_2. Заявки на переговоры.
/*
В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с
желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое
может быть удовлетворено.
Число заявок ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел — начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число — максимальное число заявок.*/



#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>


struct Request {
    int beginning;
    int end;
    const bool operator > (const Request &) const;
    const bool operator < (const Request &) const;
    const bool operator == (const Request &) const;
    const bool operator != (const Request &) const;
};

const bool Request::operator>(const Request &another) const{
    if (this->end > another.end)
        return true;
    return false;
}

const bool Request::operator<(const Request &another) const{
    if (this->end < another.end)
        return true;
    return false;
}

const bool Request::operator==(const Request &another) const{
    if (this->end == another.end)
        return true;
    return false;
}

const bool Request::operator!=(const Request &another) const{
    if (this->end != another.end)
        return true;
    return false;
}


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


void sort(My_vector<Request> vector);

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
My_vector<T>::My_vector(const My_vector &another) {
    size = another.size;
    capacity = another.capacity;
    try {
        array = new T(capacity);
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




class Time_management {
public:
    Time_management();
    void read();
    int count_max_number_request();
private:
    void delete_parallels_meet();
    My_vector<Request> req;
    int number_max_meets;
};




void Time_management::read() {
    Request time;
    while(!std::cin.eof()) {
        std::cin >> time.beginning;
        std::cin >> time.end;
        req.push_back(time);
    }
}

int Time_management::count_max_number_request() {

    std::sort(&req[0], &req[req.vector_size() - 1]);
    delete_parallels_meet();

    return number_max_meets;
}


void Time_management::delete_parallels_meet() {
    size_t j = 0;
    number_max_meets++;
        for(size_t i = 1; i < req.vector_size(); i++)
            if (req[i].beginning >= req[j].end) {
                number_max_meets++;
                j = i;
            }
}

Time_management::Time_management() {
    number_max_meets = 0;
}


int main() {
    Time_management obj1;
    obj1.read();
    std::cout << obj1.count_max_number_request();
    return 0;
}




