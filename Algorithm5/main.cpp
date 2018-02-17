#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <cstddef>




template <class T>
class My_deq {
public:
    My_deq();
    My_deq(size_t);
    ~My_deq();

    void push_back(T);
    void push_front(T);
    T pop_back();
    T pop_front();


    size_t vector_size();
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
    size = 0;
    capacity = 1024;
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
    if(size == capacity)
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
    if(size == capacity)
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
        head = array;
        tail = (array + capacity - 1);
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
        head = array;
        tail = (array + capacity - 1);
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
    capacity *= 2;
    T *temp;
    try {
        temp = new T[capacity];
    }
    catch(std::bad_alloc) {
        throw 1;
    }
    ptrdiff_t begin_head = (ptrdiff_t) (head - array);
    for (ptrdiff_t i = 0; i < begin_head; i++) {
        *(temp + i) = *(array + i);
    }
    head = temp + begin_head;

    ptrdiff_t begin_tail = (ptrdiff_t) (tail - array);
    for (ptrdiff_t i = capacity - 1; i > begin_tail; i--) {
        *(temp + i) = *(array + i);
    }

    tail = temp + begin_tail;

    delete[] array;
    array = temp;
}

template <class T>
T My_deq<T>::operator[](size_t number_element) {
    if ((number_element >= size) || (size == 0))
        return -1;
    if (tail == (array + capacity - 1))
        return *(array + number_element);
    if ((tail + 1 + number_element) >= (array + capacity))
        return *(array + number_element - (array + capacity - tail + 1));
    return *(tail + 1 + number_element);
}


class Calculate {
public:
    void read(char *);
    void count();
    int print_result();
private:
    My_deq<int> result;
    My_deq<char> opn;//обратная польская нотация
    My_deq<char> operation; //стек операций
};

void Calculate::read(char* str) {
    size_t elem_of_expression = 0;
    while (str[elem_of_expression] != '\0') {
        if (isdigit(str[elem_of_expression])) {
            opn.push_back(str[elem_of_expression]);
            elem_of_expression++;
            continue;
        }
        if (str[elem_of_expression] == '+') {  //может надо без ковычек?
            opn.push_back(' ');
            while ((operation[operation.vector_size() - 1] == '+') ||
                (operation[operation.vector_size() - 1] == '-') ||
                (operation[operation.vector_size() - 1] == '*') ||
                (operation[operation.vector_size() - 1] == '/')) {
                opn.push_back(operation.pop_back());
            }
            operation.push_back('+');
        }
        else if (str[elem_of_expression] == '-') {  //может надо без ковычек?
            opn.push_back(' ');
            while ((operation[operation.vector_size() - 1] == '-') ||
                (operation[operation.vector_size() - 1] == '+') ||
                (operation[operation.vector_size() - 1] == '*') ||
                (operation[operation.vector_size() - 1] == '/')) {
                opn.push_back(operation.pop_back());
            }
            operation.push_back('-');
        }
        else if (str[elem_of_expression] == '*') {  //может надо без ковычек?
            opn.push_back(' ');
            if ((operation[operation.vector_size() - 1] == '*') ||
                (operation[operation.vector_size() - 1] == '/')) {
                opn.push_back(operation.pop_back());
            }
            operation.push_back('*');
        }
        else if (str[elem_of_expression] == '/') {  //может надо без ковычек?
            opn.push_back(' ');
            if ((operation[operation.vector_size() - 1] == '*') ||
                (operation[operation.vector_size() - 1] == '/')) {
                opn.push_back(operation.pop_back());
            }
            operation.push_back('/');
        }
        else if (str[elem_of_expression] == '(') {
            operation.push_back('(');
        }
        else if (str[elem_of_expression] == ')') {
            while (operation[operation.vector_size() - 1] != '(')
                opn.push_back(operation.pop_back());
            operation.pop_back();
        }
        elem_of_expression++;
    }

    while (operation.vector_size() != 0)
        opn.push_back(operation.pop_back());
//    while (opn.vector_size() != 0)
//        std::cout << opn.pop_front();
}

void Calculate::count() {
    std::string number_strong_type;
    int number1;
    int number2;

    while (opn.vector_size() != 0) {
        if (isdigit(opn[0])) {
            while (isdigit(opn[0]))
                number_strong_type += opn.pop_front();
            number1 = atoi(number_strong_type.c_str());
            number_strong_type.clear();
            result.push_back(number1);
            continue;
        }
        else if (opn[0] == '+') {
            number2 = result.pop_back();
            number1 = result.pop_back();
            result.push_back(number1 + number2);
        }
        else if (opn[0] == '-') {
            number2 = result.pop_back();
            number1 = result.pop_back();
            result.push_back(number1 - number2);
        }
        else if (opn[0] == '*') {
            number2 = result.pop_back();
            number1 = result.pop_back();
            result.push_back(number1 * number2);
        }
        else if (opn[0] == '/') {
            number2 = result.pop_back();
            number1 = result.pop_back();
            result.push_back(number1 / number2);
        }
        opn.pop_front();
    }
}

int Calculate::print_result() {
    return result.pop_back();
}


int main() {
    char str[10000];
    std::cin.getline (str, 10000);
    Calculate obj1;
    obj1.read(str);
    obj1.count();
    std::cout << obj1.print_result();
    return 0;
}
