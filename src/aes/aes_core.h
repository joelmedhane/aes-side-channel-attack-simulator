#ifndef AES_H
#define AES_H

#include <stdint.h>

#define AES_STATE_SIZE 4
static const uint8_t mix_matrix[AES_STATE_SIZE][AES_STATE_SIZE];

void sub_bytes(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);
void shift_rows(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);
void mix_columns(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);

void add_round_key( uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]);

void key_expansion()

#endif