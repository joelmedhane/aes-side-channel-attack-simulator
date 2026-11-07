
#ifndef AESDROP_AES_H
#define AESDROP_AES_H

#include <stdint.h>
#include "key_expansion.h"

void aes128_encrypt(
    const uint8_t plaintext[16],
    const uint8_t words[AES_KEY_WORDS][AES_WORD_SIZE],
    uint8_t ciphertext[16]
);

#endif
