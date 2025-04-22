#include <iostream>
#include <cstdint>
using namespace std;

void generate_primes(uint32_t *buffer, size_t buffer_size, size_t n) {
    if (n < 2) return; // No primes below 2

    bool primeArray[n + 1];

    // Manual initialization
    for (size_t i = 0; i <= n; i++) {
        primeArray[i] = true;
    }
    // 0 and 1 are not considered
    primeArray[0] = primeArray[1] = false;

    for (uint32_t i = 2; i * i <= n; i++) {
        if (primeArray[i]) {
            for (uint32_t j = i * i; j <= n; j += i) {
                primeArray[j] = false;
            }
        }
    }

    // Fill buffer with primes
    size_t count = 0;
    for (uint32_t i = 2; i <= n && count < buffer_size; i++) {
        if (primeArray[i]) {
            buffer[count++] = i;
        }
    }

    for (; count < buffer_size; count++) {
        buffer[count] = 0;
    }
}

int main() {
    const size_t n = 200;
    const size_t buffer_size = 5;
    uint32_t primeArray[buffer_size];

    generate_primes(primeArray, buffer_size, n);

    for (size_t i = 0; i < buffer_size; i++) {
        if (primeArray[i] > 0) {
            cout << primeArray[i] << " ";
        }
    }

    cout << endl;
    return 0;
}
