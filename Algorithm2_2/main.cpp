#include <iostream>//вырезать метод erase
#include <vector>
#include <limits>


template <class T>
class Heap;
struct Train_Table;
size_t count_dock(Heap<Train_Table> &obj);



template <class T>
class Heap {
public:
    size_t size_heap();
    void initialize_heap(T *, size_t);
    void insert(T &);
    T pop_max();
    const T &operator[](size_t number);
private:
    std::vector<T> heap_value;
};


template <class K>
std::ostream & operator << (std::ostream &os, const Heap<K> &obj);




template <class T>
void Heap<T>::initialize_heap(T *elem_array, size_t size) {
    for (size_t i = 0; i < size; i++)
        heap_value.push_back(elem_array[i]);

    for (size_t i  = (size - 2) / 2; i < std::numeric_limits<int>::max(); i--) //цикл для верхней половины элементов т.к. size t беззнаковый
        for (size_t j = i; j <= (size - 2)/2; ) { //
            size_t k = j * 2 + 1;
            if ((k + 1) < (size) && heap_value[k] < heap_value[k + 1]) {
                k++;
            }
            if (heap_value[j] < heap_value[k]) {
                std::swap(heap_value[j], heap_value[k]);
                j = k;
            }
            else
                break;
        }
}


template <class T>
void Heap<T>::insert(T &new_elem) {
    heap_value.push_back(new_elem);
    for (size_t i = heap_value.size() - 1; i > 0;) {
        if (heap_value[i] > heap_value[(i - 1) / 2])
            std::swap(heap_value[i], heap_value[(i - 1) / 2]);
        else
            break;
        i = (i - 1) / 2;
    }
}


template <class T>
T Heap<T>::pop_max() {
    size_t number_elem = 0;
    std::swap(heap_value[number_elem], heap_value[heap_value.size() - 1]);
    for (size_t i = number_elem; (2 * i + 1) < (heap_value.size() - 1);) {
        i = (i * 2) + 1;
        if ((i + 1) < (heap_value.size() - 1) && heap_value[i] < heap_value[i + 1])
            i++;
        if (heap_value[(i - 1) / 2] < heap_value[i])
            std::swap(heap_value[(i - 1) / 2], heap_value[i]);
        else
            break;
    }
    T temp = heap_value[heap_value.size() - 1];
    heap_value.pop_back();
    return temp;
}

template <class T>
T &Heap<T>::operator[](size_t number) {
    if (number >= heap_value.size())
        throw;
    return this->heap_value[number];
}

template <class K>
std::ostream &operator<<(std::ostream &os, const Heap<K> &obj) {
    for (size_t i = 0; i < obj.heap_value.size(); i++)
        os << obj.heap_value[i] << std::endl;
    return os;
}

template <class K>
size_t Heap<K>::size_heap() {
    return heap_value.size();
}


struct Train_Table {
    size_t arrival;
    size_t departure;
    bool operator > (const Train_Table &) const ;
    bool operator == (const Train_Table &) const;
    bool operator < (const Train_Table &) const;
    friend std::ostream & operator << (std::ostream &os, const Train_Table &obj);
};

bool Train_Table::operator > (const Train_Table &another) const {
    if (this->arrival > another.arrival)
        return true;
    else if ((this->arrival == another.arrival) && (this->departure > another.departure))
        return true;
    return false;
}

bool Train_Table::operator == (const Train_Table &another) const {
    return (this->arrival == another.arrival) && (this->departure == another.departure);
}

bool Train_Table::operator<(const Train_Table &another) const {
    if (this->arrival < another.arrival)
        return true;
    else if ((this->arrival == another.arrival) && (this->departure < another.departure))
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const Train_Table &obj) {
    os << obj.arrival << " " << obj.departure << std::endl;
    return os;
}


int main() {
    Train_Table table_row;
    std::vector<Train_Table> objTable;
    size_t number;
    std::cin >> number;
    for (size_t i = 0; i < number; i++) {
        std::cin >> table_row.arrival;
        std::cin >> table_row.departure;
        objTable.push_back(table_row);
    }

    Heap<Train_Table> objHeap;
    objHeap.initialize_heap(&objTable[0], number);
    std::cout << count_dock(objHeap);
    return 0;
}



size_t count_dock(Heap<Train_Table> &obj) {
    size_t number_of_docks = 0;
    int min_depart = 0;
    std::vector<Train_Table> sorted_table;
    while (obj.size_heap() != 0) {
        sorted_table.push_back(obj.pop_max());
    }

    while (sorted_table.size() != 0) {
        min_depart = sorted_table[0].arrival;
        sorted_table.erase(sorted_table.begin());
        number_of_docks++;
        for (size_t i = 0; i < sorted_table.size();) {
            if (min_depart >= sorted_table[i].departure + 1) {
                min_depart = sorted_table[i].arrival;
                sorted_table.erase((sorted_table.begin() + i));
            } else
                i++;
        }
    }
    return number_of_docks;
}