#include <utility>
#include <cstdint>
#include <iostream>

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


int main() {
    uint32_t num = 29;
    auto [minVal, maxVal] = find_min_max_with_same_bit_count(num);
    std::cout << "Input: " << num << std::endl;
    std::cout << "Min with same bits: " << minVal << std::endl;
    std::cout << "Max with same bits: " << maxVal << std::endl;
}