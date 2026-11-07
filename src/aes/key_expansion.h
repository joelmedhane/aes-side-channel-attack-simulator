
#ifndef AESDROP_KEY_EXPANSION_H
#define AESDROP_KEY_EXPANSION_H

#include <stdint.h>

#define AES_KEY_WORDS 44
#define AES_WORD_SIZE 4

void key_expansion(const uint8_t key[4][4], uint8_t words[AES_KEY_WORDS][AES_WORD_SIZE]);

#endif
