#include <iostream>
#include <cmath>

//1_*.​ Найти все простые числа в диапазоне [2..n] за O(n).


bool *is_prime(int number);

int main() {
    int max_number;
    bool *buffer_prime;
    std::cin >> max_number;
    buffer_prime = is_prime(max_number);
    for (size_t i = 0; i <= max_number; i++)
        if (buffer_prime[i] == true)
            std::cout << i << " ";

    delete buffer_prime;
    return 0;
}

bool *is_prime(int number) {
    bool *vector_prime = new bool [number + 1];
    int squart_number = (int)sqrt(number);

    vector_prime[2] = true;
    vector_prime[3] = true;

    for (size_t i = 1; i <= squart_number; i++)
        for (size_t j = 1; j <= squart_number; j++) {
            int i_square = i*i;
            int j_square = j*j;
            int n = 4 * i_square + j_square;

            if (n <= number && ((n % 12 == 1) || (n % 12 == 5)))
                vector_prime[n] = true;

            n -= i_square;

            if (n <= number && (n % 12 == 7))
                vector_prime[n] = true;

            n -= 2*j_square;

            if (i > j && n < number && (n % 12 == 11))
                vector_prime[n] = true;
        }

    for (size_t k = 5; k <= squart_number; k += 2)
        if (vector_prime[k]) {
            size_t l = k * k;
            for (size_t m = l; m <= number; m += l)
                vector_prime[m] = false;
        }

    return vector_prime;
}