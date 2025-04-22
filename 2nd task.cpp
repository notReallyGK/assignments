#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

void analyze_word_lengths(const char *text, uint32_t *length_counts, size_t max_length) {
    memset(length_counts, 0, sizeof(uint32_t) * (max_length + 2));
    uint32_t currentLength = 0; //basically a counter
    uint8_t wordsCounter = 0;
    while (*text != '\0') {
        currentLength++;
        // checking if '\0' will be next, if so then counts the length of the last word.
        if (*(text + 1) == '\0') {
            length_counts[currentLength]++;
            break;
        }
        // can be extended with other conditions
        if (*text == '\n' || *text == '\t' || *text == ' ') {
            if (currentLength > max_length) wordsCounter++;
            length_counts[currentLength - 1]++;
            currentLength = 0;
        }
        ++text;
    }
    //amount of words that larger than max_length
    length_counts[0] = wordsCounter-1;
}

int main()
{
    size_t max_length = 7;
    uint32_t length_counts[max_length+2];
    char text[] = "And nothing goes to     waste he said I \t wish I could \n do more for you working different different different different different different";
    analyze_word_lengths(text, length_counts, max_length);
    cout << "words larger than max_length: " << length_counts[0] << endl;
    for (uint32_t i = 1; i < max_length+1; i++) cout << "Words with (" << i << ") letters: " << length_counts[i] << endl;

}
