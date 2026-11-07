#include "key_expansion.h"
#include "sbox.h"

#define AES128_NK 4

static const uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1B, 0x36
};

/* Rotate a word one byte to the left. */
static void rot_word(uint8_t word[AES_WORD_SIZE]) {
    uint8_t first = word[0];

    for (int i = 1; i < AES_WORD_SIZE; i++) {
        word[i - 1] = word[i];
    }

    word[AES_WORD_SIZE - 1] = first;
}

/* Expand a 128-bit key into 44 words. */
void key_expansion( const uint8_t key[4][4], uint8_t words[AES_KEY_WORDS][AES_WORD_SIZE]) {
    /* Copy the original key into the first four words. */
    for (int i = 0; i < AES128_NK; i++) {
        for (int j = 0; j < AES_WORD_SIZE; j++) {
            words[i][j] = key[j][i];
        }
    }

    /* Generate the remaining 40 words. */
    for (int i = AES128_NK; i < AES_KEY_WORDS; i++) {
        uint8_t temp[AES_WORD_SIZE];

        for (int j = 0; j < AES_WORD_SIZE; j++) {
            temp[j] = words[i - 1][j];
        }

        if (i % AES128_NK == 0) {
            rot_word(temp);
            aes_substitute_bytes(temp, AES_WORD_SIZE);
            temp[0] ^= rcon[i / AES128_NK - 1];
        }

        for (int j = 0; j < AES_WORD_SIZE; j++) {
            words[i][j] = words[i - AES128_NK][j] ^ temp[j];
        }
    }
}
