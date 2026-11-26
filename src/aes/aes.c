#include "aes.h"
#include "aes_core.h"

#define AES128_NR 10

void aes128_encrypt(const uint8_t plaintext[16], const uint8_t words[AES_KEY_WORDS][AES_WORD_SIZE],uint8_t ciphertext[16], void (*callback)(uint8_t, uint8_t)) {
    uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE];

  
    for (int r = 0; r < AES_STATE_SIZE; r++) {
        for (int c = 0; c < AES_STATE_SIZE; c++) {
            state[r][c] = plaintext[4 * c + r];
        }
    }


    add_round_key(state, words, 0);


    for (int round = 1; round < AES128_NR; round++) {
        sub_bytes(state, callback);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, words, round);
    }

   
    sub_bytes(state, callback);
    shift_rows(state);
    add_round_key(state, words, AES128_NR);


    for (int r = 0; r < AES_STATE_SIZE; r++) {
        for (int c = 0; c < AES_STATE_SIZE; c++) {
            ciphertext[4 * c + r] = state[r][c];
        }
    }
}
