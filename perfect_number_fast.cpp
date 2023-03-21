#include <iostream>
#include <cmath>
#include <cstdint>
#include <immintrin.h>
#include <cstdint>
using namespace std;

bool is_prime(uint64_t n) {
    if (n <= 1) {
        return false;
    }
    for (uint64_t i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    uint64_t p[] = {2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107}; // list of Mersenne prime exponents
    uint64_t max_n = 0;
    for (int i = 0; i < 11; i++) {
        uint64_t n = pow(2, p[i]) - 1; // calculate the Mersenne prime
        if (is_prime(n)) {
            uint64_t perfect_num = pow(2, p[i] - 1) * n; // calculate the perfect number
            cout << "The biggest perfect number based on Mersenne prime " << p[i] << " is " << perfect_num << endl;
            max_n = max(max_n, perfect_num);
        }
    }
    cout << "The overall biggest perfect number based on Mersenne primes is " << max_n << endl;
    return 0;
}
