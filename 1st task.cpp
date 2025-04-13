#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;

void generate_primes(uint32_t *buffer, size_t buffer_size, size_t n) {
    uint32_t i = 2;
    uint32_t j;
    uint8_t counter = 0;
    bool primeArray[buffer_size];
    memset(primeArray, true, sizeof(primeArray));
    do {
        do {
            j = i*i + i*counter;
            primeArray[j] = false;
            counter++;
        } while (j <=n);
        counter = 0;
        i++;
    } while (i*i <= n);

    for (size_t num = 0; num < buffer_size; num++) {
        if (primeArray[num] == true) {
            buffer[num] = num;
        } else {buffer[num] = 0;}
    }
}


int main() {
    size_t n = 30;
    uint32_t primeArray[n];
    generate_primes(primeArray, n, n);
    for (size_t i = 0; i < n; i++) { if (primeArray[i] > 0) cout << primeArray[i] << " ";}

}