#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Function under test
void analyze_word_lengths(const char *text, uint32_t *length_counts, size_t max_length) {
    memset(length_counts, 0, sizeof(uint32_t) * (max_length + 2));
    uint32_t currentLength = 0; // basically a counter
    uint8_t wordsCounter = 0;
    while (*text != '\0') {
        currentLength++;
        if (*(text + 1) == '\0') {
            length_counts[currentLength]++;
            break;
        }
        if (*text == '\n' || *text == '\t' || *text == ' ') {
            if (currentLength > max_length) wordsCounter++;
            length_counts[currentLength - 1]++;
            currentLength = 0;
        }
        ++text;
    }
    length_counts[0] = wordsCounter;
}

// ---------------- TESTS ----------------

TEST(AnalyzeWordLengthsTest, BasicSentenceTest) {
    const size_t max_length = 5;
    uint32_t counts[max_length + 2];
    const char* text = "This is a test";

    analyze_word_lengths(text, counts, max_length);

    // Word lengths: 4, 2, 1, 4
    // So counts[1]=1, counts[2]=1, counts[4]=2
    EXPECT_EQ(counts[0], 0); // no long words
    EXPECT_EQ(counts[1], 1);
    EXPECT_EQ(counts[2], 1);
    EXPECT_EQ(counts[3], 0);
    EXPECT_EQ(counts[4], 2);
    EXPECT_EQ(counts[5], 0);
}

TEST(AnalyzeWordLengthsTest, HandlesTabsAndNewlines) {
    const size_t max_length = 4;
    uint32_t counts[max_length + 2];
    const char* text = "Hi\tthere\nbuddy";

    analyze_word_lengths(text, counts, max_length);

    // Word lengths: 2 (Hi), 5 (there), 5 (buddy)
    EXPECT_EQ(counts[0], 1);  // Only 1 word over max_length
    EXPECT_EQ(counts[1], 0);
    EXPECT_EQ(counts[2], 1);
    EXPECT_EQ(counts[3], 0);
    EXPECT_EQ(counts[4], 0);
    EXPECT_EQ(counts[5], 0);  
}

TEST(AnalyzeWordLengthsTest, EmptyInput) {
    const size_t max_length = 5;
    uint32_t counts[max_length + 2];
    const char* text = "";

    analyze_word_lengths(text, counts, max_length);

    for (size_t i = 0; i <= max_length + 1; ++i) {
        EXPECT_EQ(counts[i], 0);
    }
}

TEST(AnalyzeWordLengthsTest, LongWordHandling) {
    const size_t max_length = 4;
    uint32_t counts[max_length + 2];
    const char* text = "tiny supercalifragilisticexpialidocious tiny big";

    analyze_word_lengths(text, counts, max_length);

    // "tiny" = 4, "super..." > max_length, "tiny" = 4, "big" = 3
    EXPECT_EQ(counts[0], 0);
    EXPECT_EQ(counts[3], 1);
    EXPECT_EQ(counts[4], 2);
}

TEST(AnalyzeWordLengthsTest, WordsExactlyAtMaxLength) {
    const size_t max_length = 5;
    uint32_t counts[max_length + 2];
    const char* text = "apple pears plums melon";

    analyze_word_lengths(text, counts, max_length);

    // All words are 5 letters
    EXPECT_EQ(counts[0], 0);
    EXPECT_EQ(counts[5], 4);
}

