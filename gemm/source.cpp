#include "source.h"
// #include "hls_half.h"
#include <hls_stream.h>

void matrix_multiply(
    half A[MATRIX_SIZE][MATRIX_SIZE],
    half B[MATRIX_SIZE][MATRIX_SIZE],
    half C[MATRIX_SIZE][MATRIX_SIZE]) {
    
    #pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=B offset=slave bundle=gmem1
    #pragma HLS INTERFACE m_axi port=C offset=slave bundle=gmem2
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    
    // Local buffers for tiling
    half A_local[TILE_SIZE][TILE_SIZE];
    half B_local[TILE_SIZE][TILE_SIZE];
    half C_local[TILE_SIZE][TILE_SIZE];
    
    // Initialize C_local
    for(int i = 0; i < TILE_SIZE; i++) {
        for(int j = 0; j < TILE_SIZE; j++) {
            #pragma HLS PIPELINE
            C_local[i][j] = 0;
        }
    }
    
    // Main computation loops
    L1: for(int i = 0; i < MATRIX_SIZE; i++) {
        L2: for(int j = 0; j < MATRIX_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            half sum = 0;
            L3: for(int k = 0; k < MATRIX_SIZE; k++) {
                #pragma HLS UNROLL factor=8
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// Define a top-level function for Vitis HLS synthesis
extern "C" {
void top_matrix_multiply(
    half A[MATRIX_SIZE][MATRIX_SIZE],
    half B[MATRIX_SIZE][MATRIX_SIZE],
    half C[MATRIX_SIZE][MATRIX_SIZE]) {
    
    // Call the matrix_multiply function
    matrix_multiply(A, B, C);
}
}