
#include "aes_core.h"
#include "sbox.h"

#define POLYNOMIAL_REDUCER 0x1B

static const uint8_t mix_matrix[AES_STATE_SIZE][AES_STATE_SIZE] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};


void shift_rows(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]) {
    
    for (int r = 1; r < AES_STATE_SIZE; r++) {
        uint8_t original_row[AES_STATE_SIZE];

        for (int c = 0; c < AES_STATE_SIZE; c++) {
            original_row[c] = state[r][c];
        }

        for (int c = 0; c < AES_STATE_SIZE; c++) {
            state[r][c] = original_row[(c + r) % AES_STATE_SIZE];
        }
    }
}


void sub_bytes(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]) {
    for (int r = 0; r < AES_STATE_SIZE; r++) {
        aes_substitute_bytes(state[r], AES_STATE_SIZE);
    }
}


void add_round_key(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE], const uint8_t words[44][4], int round) {
    for (int r = 0; r < AES_STATE_SIZE; r++) {
        for (int c = 0; c < AES_STATE_SIZE; c++) {
            state[r][c] ^= words[4 * round + c][r];
        }
    }
}



/* Multiply by x in GF(2^8), reducing with AES's polynomial. */
static uint8_t xtime(uint8_t value) {
    uint8_t high_bit = value & 0x80;
    value = (uint8_t)(value << 1);

    if (high_bit) {
        value ^= POLYNOMIAL_REDUCER;

    }

    return value;
}


static uint8_t gf_multiply(uint8_t a, uint8_t b) {
    uint8_t result = 0;

    for (int bit = 0; bit < 8; bit++) {

        if ((b >> bit) & 1u) {
            result ^= a;

        }

        a = xtime(a);
    }
    return result;
}

void mix_columns(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]) {
    /* Each column must be fully computed before the original is overwritten. */

    for (int c = 0; c < AES_STATE_SIZE; c++) {
        uint8_t new_column[AES_STATE_SIZE];

        for (int r = 0; r < AES_STATE_SIZE; r++) {
            uint8_t accumulated = 0;

            for (int i = 0; i < AES_STATE_SIZE; i++) {
                accumulated ^= gf_multiply(mix_matrix[r][i], state[i][c]);

            }

            new_column[r] = accumulated;
        }

        for (int r = 0; r < AES_STATE_SIZE; r++) {
            state[r][c] = new_column[r];

        }
    }
}