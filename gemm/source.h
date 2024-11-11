#ifndef __MATRIX_MULTIPLY_H__
#define __MATRIX_MULTIPLY_H__

// #include "hls_half.h"
#include <ap_int.h>
#include <ap_fixed.h>
#define half float
// Define matrix dimensions
#define MATRIX_SIZE 32
#define TILE_SIZE 16

// Function declarations
void matrix_multiply(
    half A[MATRIX_SIZE][MATRIX_SIZE],
    half B[MATRIX_SIZE][MATRIX_SIZE],
    half C[MATRIX_SIZE][MATRIX_SIZE]);

// Declare the top-level function for Vitis HLS synthesis
extern "C" {
    void top_matrix_multiply(
        half A[MATRIX_SIZE][MATRIX_SIZE],
        half B[MATRIX_SIZE][MATRIX_SIZE],
        half C[MATRIX_SIZE][MATRIX_SIZE]);
}

// Optional: Define data types for optimization if needed
// typedef half DATA_TYPE;
// typedef ap_uint<16> INDEX_TYPE;

#endif // __MATRIX_MULTIPLY_H__
