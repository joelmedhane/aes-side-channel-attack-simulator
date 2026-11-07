#ifndef AESDROP_SBOX_H
#define AESDROP_SBOX_H

#include <stdint.h>
#include <stddef.h>

void aes_substitute_bytes(uint8_t *bytes, size_t length);

#endif