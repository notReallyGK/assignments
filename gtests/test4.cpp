#include <gtest/gtest.h>
#include <utility>
#include <cstdint>

std::pair<uint32_t, uint32_t> find_min_max_with_same_bit_count(uint32_t number) {
    uint32_t bitCount = 0;
    uint32_t temp = number;
    while (temp) {
        bitCount += temp & 1; //counting bits
        temp >>= 1;
    }

    //min condition, it creates a number of one-bits in a row, starting with the lowest digits
    uint32_t minValue = (1U << bitCount) - 1; //shifts 1 bit to the left, basically this is 2 in the power of bitCount

    // max condition, the loop iterates from bit position 31 down to 0
    uint32_t maxValue = 0;
    for (int i = 31; bitCount > 0 && i >= 0; --i, --bitCount) { //bit 31 is being the most significant
        maxValue |= (1U << i); //shifts 1 bit to the left until the end, and maxValue equates to its greater value
    }
    return {minValue, maxValue};
}

// -------- TESTS --------

TEST(FindMinMaxSameBitCountTest, ZeroBits) {
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(0);
    EXPECT_EQ(minVal, 0);
    EXPECT_EQ(maxVal, 0);
}

TEST(FindMinMaxSameBitCountTest, OneBitSet) {
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(8); // 00001000
    EXPECT_EQ(minVal, 1);     // 00000001
    EXPECT_EQ(maxVal, 1U << 31); 
}

TEST(FindMinMaxSameBitCountTest, ThreeBitsSet) {
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(29); // 11101 has 4 bits set
    EXPECT_EQ(minVal, 15);        // 1111
    EXPECT_EQ(maxVal, 15U << 28); 
}

TEST(FindMinMaxSameBitCountTest, AllBitsSet) {
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(0xFFFFFFFF); // all 32 bits
    EXPECT_EQ(minVal, 0xFFFFFFFF);
    EXPECT_EQ(maxVal, 0xFFFFFFFF);
}

TEST(FindMinMaxSameBitCountTest, AlternatingBits) {
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(0xAAAAAAAA); // 10101010...
    // This has 16 bits set
    EXPECT_EQ(minVal, (1U << 16) - 1); // 16 ones: 0xFFFF
    EXPECT_EQ(maxVal, 0xFFFF0000);     
}
