
#ifndef AESDROP_AES_CORE_H
#define AESDROP_AES_CORE_H

#include <stdint.h>
#include "key_expansion.h"

#define AES_STATE_SIZE 4

/* AES state is indexed as state[row][column]. */
void sub_bytes(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE], void (*callback)(uint8_t, uint8_t));
void shift_rows(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);
void mix_columns(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);
void add_round_key(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE], const uint8_t words[AES_KEY_WORDS][AES_WORD_SIZE], int round
);

#endif
