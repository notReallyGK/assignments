#include <gtest/gtest.h>
#include <cstdint>
#include <cstddef>

// -------------------------------
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
// -------------- HELPERS -----------------

// Helper function to compare arrays
bool arrays_equal(const uint32_t* a, const uint32_t* b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// ----------------- TESTS -----------------
TEST(GeneratePrimesTest, SmallPrimesCorrectness) {
    const size_t buffer_size = 10;
    uint32_t buffer[buffer_size];
    generate_primes(buffer, buffer_size, 30);

    uint32_t expected[buffer_size] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    EXPECT_TRUE(arrays_equal(buffer, expected, buffer_size));
}

TEST(GeneratePrimesTest, LargerBufferThanPrimes) {
    const size_t buffer_size = 15;
    uint32_t buffer[buffer_size];
    generate_primes(buffer, buffer_size, 10);

    uint32_t expected[buffer_size] = {2, 3, 5, 7};
    for (size_t i = 4; i < buffer_size; ++i) {
        expected[i] = 0;
    }

    EXPECT_TRUE(arrays_equal(buffer, expected, buffer_size));
}

TEST(GeneratePrimesTest, BufferSizeZero) {
    uint32_t buffer[1]; // dummy
    generate_primes(buffer, 0, 100);
    SUCCEED(); // doesn't crash
}

TEST(GeneratePrimesTest, NoPrimesForSmallN) {
    const size_t buffer_size = 5;
    uint32_t buffer[buffer_size];
    generate_primes(buffer, buffer_size, 1);

    uint32_t expected[buffer_size] = {0, 0, 0, 0, 0};
    EXPECT_TRUE(arrays_equal(buffer, expected, buffer_size));
}

TEST(GeneratePrimesTest, ExactNumberOfPrimes) {
    const size_t buffer_size = 4;
    uint32_t buffer[buffer_size];
    generate_primes(buffer, buffer_size, 10);

    uint32_t expected[buffer_size] = {2, 3, 5, 7};
    EXPECT_TRUE(arrays_equal(buffer, expected, buffer_size));
}
