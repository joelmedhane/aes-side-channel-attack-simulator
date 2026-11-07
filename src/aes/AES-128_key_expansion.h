#ifndef AES_128_KEY_EXPANSION_H
#define AES_128_KEY_EXPANSION_H

#include <stdint.h>

#define AES_KEY_WORDS 44
#define AES_WORD_SIZE 4

void key_expansion(
    const uint8_t key[4][4],
    uint8_t word[AES_KEY_WORDS][AES_WORD_SIZE]
);

void rot_word(uint8_t word[4]);

void sub_word(uint8_t word[4]);

#endif