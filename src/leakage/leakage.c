
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


// only temporary fix

static double sigma = 1.0;
static double alpha = 1.0;


void record_leakage(uint8_t old_value, uint8_t new_value) {
    double measurement = simulate_leakage(old_value, new_value);

    printf("Old: %02X, New: %02X, Leakage: %.4f\n",
           (unsigned int)old_value,
           (unsigned int)new_value,
           measurement);
}

double simulate_leakage(uint8_t old_value, uint8_t new_value) {
    return alpha * hamming_distance(old_value, new_value)
           + gaussian_noise(sigma);
}


int hamming_weight (uint8_t value){
    return __builtin_popcount(value);
}

int hamming_distance (uint8_t a, uint8_t b){
    return hamming_weight(a ^ b);

}

/**
 * 
 * 
 * Box Muller transformation of uniform distrubution to normal distrubution
 * 
 * 
 */

double gaussian_noise(double sigma){
    double u1 = (rand() + 1.0) / (RAND_MAX + 2.0);
    double u2 = (rand() + 1.0) / (RAND_MAX + 2.0);

    return sigma * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);



}