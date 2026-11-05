
#include "AES-128_sbox.h"



//ROTWORD([a0, a1, a2, a3]) = [a1, a2, a3, a0], 
/**
 * 
 * @brief, this function shifts a word left at byte size;
 * 
 * @param, will be an array of 4 entries each 4 bits which corresponds to a whole word
 * 
 * 
 */

void rot_word(uint8_t word[4]){

    uint8_t first = word[0];

    for(int i = 1; i < 4; i++){
        word[i-1] = word[i];

    }
    word[3] = first;

}

/**
 * 
 * 
 * 
 * @todo for modularity it would be good to have a function SubBytes and SubWords that handle both cases and eliminates code duplicity.
 */

void sub_word(uint8_t word[4]){

    for(int i = 0; i < 4; i++){
        word[i] = sbox[word[i]];

    }

}