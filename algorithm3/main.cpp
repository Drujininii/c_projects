#include <iostream>
#include <cassert>


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

    My_vector & operator=(My_vector &);
    T operator[](size_t);
private:
    void resize();
    size_t size;
    size_t capacity;
    T *array;
};




class Find_nearest_elem {
public:
    void read();
    void find_nearest_el(int, size_t, size_t);
    void print_vector_idx();
    void find_border();

private:
    My_vector <int> first;//операция чтения не делает проверку на валидность
    My_vector <int> second;
    My_vector <size_t> vector_idx;
};

void Find_nearest_elem::read() {
    size_t size1;
    size_t size2;
    int temp;
    std::cin >> size1;
    for (size_t i = 0; i < size1; i++) {
        std::cin >> temp;
        first.push_back(temp);
    }

    std::cin >> size2;
    for (size_t i = 0; i < size2; i++) {
        std::cin >> temp;
        second.push_back(temp);
    }
}

void Find_nearest_elem::find_nearest_el(int elem, size_t left_border, size_t right_border) {
    size_t gap = 0;
        while (left_border != right_border - 1) {
            gap = (left_border + right_border)/2;
            if (elem < first[gap])
                right_border = gap;
            if (elem > first[gap])
                left_border = gap;
            if (elem == first[gap]) {
                vector_idx.push_back(gap);
                return;
            }
        }
        //устраняем неоднозначность в указатели на элемент т.к. элемент может быть либо ближе к gap либо gap +-1
        if(abs(elem - first[left_border]) > abs(elem - first[right_border]))
            vector_idx.push_back(right_border);
        else
            vector_idx.push_back(left_border);
}

void Find_nearest_elem::print_vector_idx() {
    for (size_t i = 0; i < vector_idx.vector_size(); i++)
        std::cout << " " << vector_idx[i];
}

void Find_nearest_elem::find_border() {
    size_t number_second_el = 0;
    for (; number_second_el < second.vector_size(); number_second_el++) {
        size_t right_border = 2;
        size_t left_border = 0;
        if (second[number_second_el] < first[left_border]) {
            vector_idx.push_back(left_border);
            continue;
        }
        for (; right_border < first.vector_size(); right_border *= 2) {
            if ((second[number_second_el] >= first[left_border]) &&
                (second[number_second_el] < first[right_border])) {//ищем элемент в пределах отрезка и идем дальше
                find_nearest_el(second[number_second_el], left_border, right_border);
                break;
            }
            left_border = right_border;
        }
        if (right_border >= first.vector_size()) {
            if(left_border == first.vector_size() - 1) {
                vector_idx.push_back(left_border);
                continue;
     
}


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
}       }
            find_nearest_el(second[number_second_el], left_border, first.vector_size() - 1);
        }
    }
}


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



int main() {
    Find_nearest_elem object;
    object.read();
    object.find_border();
    object.print_vector_idx();
    return 0;
}
