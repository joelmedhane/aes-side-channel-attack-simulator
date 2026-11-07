
#include "AES-128.h"
#include "AES-128_sbox.h"

#define POLYNOMIAL_REDUCER 0x1B

static const uint8_t mix_matrix[AES_STATE_SIZE][AES_STATE_SIZE] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};



void shift_rows(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]){
    // the number of positions the bytes are shifted depends on the row index r 
    //given index r,c becomes r , (r+c) mod 4 where 0 <= r, c < 4
    // which means the first row will be unaffacted from the changes here

    for (int r = 1; r < AES_STATE_SIZE; r++) {
        uint8_t temp[AES_STATE_SIZE];

        // Save the original row
        for (int c = 0; c < AES_STATE_SIZE; c++) {
            temp[c] = state[r][c];
        }

        // Shift the row
        for (int c = 0; c < AES_STATE_SIZE; c++) {
            state[r][c] = temp[(c + r) % 4];
        }
    }
}


void sub_bytes(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]){
    
    for(int r = 0; r < AES_STATE_SIZE; r++){

        for(int c = 0; c < AES_STATE_SIZE; c++){

            state[r][c] = sbox[state[r][c]];

        }
    }
}


void add_round_key(
    uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE],
    const uint8_t round_key[AES_STATE_SIZE][AES_STATE_SIZE]
) {

    for(int r = 0; r < AES_STATE_SIZE; r++){
        for(int c = 0; c < AES_STATE_SIZE; c++){
            state[r][c] = state[r][c] ^ round_key[r][c];
        }
    }
}



/**
 * 
 * @return we return an in update to make life easier and not have to create new variables and switching storing etc.
 * 
 * 
 */

void xTimes(uint8_t * b){

    if((*b >> 7) == 1){ // chosing shifting instead of b & 2^7 != 0, because shifting is a faster operation than power
                     // so now if this value == 1 then we know there will be an overflow when we multiply with x.
        *b <<= 1;
        *b = *b ^ POLYNOMIAL_REDUCER;

    } else {
        *b <<= 1;
    }
}



/**
 * 
 * 
 * 
 * @argument we know that both matrixes are 4x4 so, there is no need to check the sizes of the matrix
 * 
 * 
 * 
 * the row denotes the round key matrix and the column denotes the state matrix column
 * the most nested loop is for calculating the dot project between different 
 * 
 * I think it can be calculated using only two foor loops and not more but that depends on if i am smart enoguh to do it.
 * 
 * 
 * 
 */
void mix_columns(uint8_t state[AES_STATE_SIZE][AES_STATE_SIZE]){


    /**
     * we iterate over the columns of the roundKey matrix 
     * first before so we can store the columns in a temporary array of 4 bytes and then
     * continsously update it saving storage.
     * 
     *  */ 


    
    uint8_t tempArray [AES_STATE_SIZE]; // only four elements are needed.

    

    for(int c = 0; c < AES_STATE_SIZE; c++){
        for(int r = 0; r < AES_STATE_SIZE; r++){
            uint8_t dotAcc = 0;

            for(int i = 0; i < AES_STATE_SIZE; i++){

                uint8_t gfAcc = 0;
                uint8_t stateValue = mix_matrix[r][i];

                for(int j = 0; j < 8; j++){

                    if ((state[i][c] >> j) & 0x01) {
                        gfAcc ^= stateValue;
                    }

                    xTimes(&stateValue);

                }

                dotAcc = dotAcc ^ gfAcc;

            }

            tempArray[r] = dotAcc;
        }

        for (int r = 0; r < AES_STATE_SIZE; r++) {
            state[r][c] = tempArray[r];
        }
    }

}




