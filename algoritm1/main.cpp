//​Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и
//вычитания (умножением пользоваться нельзя).
//n ≤ 1000.


#include <iostream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <cstdlib>

uint32_t is_num(char *);

class square {
public:
    square(uint32_t);
    uint32_t to_square();

private:
    uint32_t current_number;
    uint32_t current_square_number;
    uint32_t difference;
    uint32_t max_number_to_square;
};


square::square(uint32_t number) {
    current_number = 1;
    current_square_number = 0;
    difference = 1;
    assert(number != 0);
    max_number_to_square = number;
}


uint32_t square::to_square() {//для возведения в квадрат прибавляем разницу между квадратами соседних элементов,
    //которая увеличивается на 2 при каждом следущем шаге
    assert(current_number <= max_number_to_square);
    current_square_number += difference;
    difference += 2;
    current_number++;
    return current_square_number;
}


int main() {
    int n = 0;
    std::cin >> n;

    char max_number[5];
    std::cin.exceptions(std::ios::failbit);

    try {
        std::cin.getline(max_number, 5);
    }
    catch(std::ios::failure& e) {
        assert(0);
    }

    uint32_t max_number_ui = is_num(max_number);
    assert(max_number_ui <= 1000);
    square sq(max_number_ui);
//можно все разложить по функциям, но в "минимальных рпавилах кодирования" сказано о необходиомсти чтения в мэйне (?)
    for (uint32_t i = 0; i < max_number_ui; i++) {
        if(i > 0)
            std::cout << " ";
        std::cout << sq.to_square();
    }

    return 0;
}


uint32_t is_num(char *buffer){
    size_t i = 0;
    while(*(buffer + i) != '\0') {
        assert(isdigit(*(buffer + i)));
        i++;
    }
    uint32_t num = (uint32_t) atoi(buffer);
    return num;
}