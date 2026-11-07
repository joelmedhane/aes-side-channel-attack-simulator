#include <stdint.h>
#include "AES-128_sbox.h"

#define NK 4
#define NR 10
#define WORD_SIZE 4
#define TOTAL_WORDS 44

static const uint8_t RCON[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1B, 0x36
};

/**
 * @brief Rotates a 4-byte word one byte to the left.
 * @param word The word to rotate in place.
 */
void rot_word(uint8_t word[4]) {

    uint8_t first = word[0];

    for (int i = 1; i < WORD_SIZE; i++) {
        word[i - 1] = word[i];
    }

    word[3] = first;
}

/**
 * @brief Applies the AES S-box to each byte of a word.
 * @param word The word to substitute in place.
 */
void sub_word(uint8_t word[4]) {

    for (int i = 0; i < WORD_SIZE; i++) {
        word[i] = sbox[word[i]];
    }
}

/**
 * @brief Expands a 128-bit AES key into 44 words.
 *
 * @param key Original AES key represented as a 4x4 matrix.
 * @param word Output array containing 44 words of 4 bytes each.
 */
void key_expansion(
    const uint8_t key[4][4],
    uint8_t word[TOTAL_WORDS][WORD_SIZE]
) {

    int i = 0;

    // Copy the original key into the first four words
    while (i < NK) {

        for (int j = 0; j < WORD_SIZE; j++) {
            word[i][j] = key[j][i];
        }

        i++;
    }

    // Generate the remaining 40 words
    while (i <= 4 * NR + 3) {

        uint8_t temp[WORD_SIZE];

        // temp = w[i - 1]
        for (int j = 0; j < WORD_SIZE; j++) {
            temp[j] = word[i - 1][j];
        }

        if (i % NK == 0) {

            rot_word(temp);
            sub_word(temp);

            // Apply Rcon to the first byte
            temp[0] ^= RCON[i / NK - 1];

        } else if (NK > 6 && (i % NK) == 4) {

            sub_word(temp);
        }

        // w[i] = w[i - Nk] XOR temp
        for (int j = 0; j < WORD_SIZE; j++) {
            word[i][j] = word[i - NK][j] ^ temp[j];
        }

        i++;
    }
}