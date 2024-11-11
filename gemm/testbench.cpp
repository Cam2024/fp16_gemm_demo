#include <iostream>
#include "source.h"
// #include "hls_half.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to initialize matrix with random values
void init_matrix(half matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            // Generate random values between -1 and 1
            float rand_val = (float)rand() / RAND_MAX * 2.0f - 1.0f;
            matrix[i][j] = (half)rand_val;
        }
    }
}

// Function to verify results
void verify_result(half A[MATRIX_SIZE][MATRIX_SIZE], 
                  half B[MATRIX_SIZE][MATRIX_SIZE], 
                  half C[MATRIX_SIZE][MATRIX_SIZE]) {
    // Calculate reference result using standard multiplication
    half C_ref[MATRIX_SIZE][MATRIX_SIZE];
    float max_error = 0.0f;
    
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            half sum = 0;
            for(int k = 0; k < MATRIX_SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C_ref[i][j] = sum;
            
            // Calculate error
            float error = std::abs((float)C_ref[i][j] - (float)C[i][j]);
            max_error = std::max(max_error, error);
        }
    }
    
    std::cout << "Maximum Error: " << max_error << std::endl;
    if(max_error < 0.1) { // Threshold for half precision
        std::cout << "Test Passed!" << std::endl;
    } else {
        std::cout << "Test Failed!" << std::endl;
    }
}

int main() {
    // Declare matrices
    half A[MATRIX_SIZE][MATRIX_SIZE];
    half B[MATRIX_SIZE][MATRIX_SIZE];
    half C[MATRIX_SIZE][MATRIX_SIZE];
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize input matrices
    std::cout << "Initializing matrices..." << std::endl;
    init_matrix(A);
    init_matrix(B);
    
    // Call the DUT (Device Under Test)
    std::cout << "Running matrix multiplication..." << std::endl;
    top_matrix_multiply(A, B, C);  // 修改为顶层函数 top_matrix_multiply
    
    // Verify results
    std::cout << "Verifying results..." << std::endl;
    verify_result(A, B, C);
    
    return 0;
}
