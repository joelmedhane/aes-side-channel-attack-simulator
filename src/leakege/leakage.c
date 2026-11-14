





int hamming_weight (uint8_t value){
    return __builtin_popcount(value);
}

int hamming_distance (uint8_t a, uint8_t b){
    return hamming_weight(a ^ b);

}