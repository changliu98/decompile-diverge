void mtxMultiply(float *result, float *matrixA, float *matrixB)
{
    // Calculate element [0][0] of the result matrix (row 0 of lhs dot col 0 of rhs)
    result[0] = matrixA[0xc] * matrixB[3] + matrixA[8] * matrixB[2] + *matrixA * *matrixB + matrixA[4] * matrixB[1];
    
    // Calculate element [0][1] of the result matrix (row 0 of lhs dot col 1 of rhs)
    result[1] = matrixA[0xd] * matrixB[3] + matrixA[9] * matrixB[2] + matrixA[1] * *matrixB + matrixA[5] * matrixB[1];
    
    // Calculate element [0][2] of the result matrix (row 0 of lhs dot col 2 of rhs)
    result[2] = matrixA[0xe] * matrixB[3] + matrixA[10] * matrixB[2] + matrixA[2] * *matrixB + matrixA[6] * matrixB[1];
    
    // Calculate element [0][3] of the result matrix (row 0 of lhs dot col 3 of rhs)
    result[3] = matrixA[0xf] * matrixB[3] + matrixA[0xb] * matrixB[2] + matrixA[3] * *matrixB + matrixA[7] * matrixB[1];
    
    // Calculate element [1][0] of the result matrix (row 1 of lhs dot col 0 of rhs)
    result[4] = matrixA[0xc] * matrixB[7] + matrixA[8] * matrixB[6] + *matrixA * matrixB[4] + matrixA[4] * matrixB[5];
    
    // Calculate element [1][1] of the result matrix (row 1 of lhs dot col 1 of rhs)
    result[5] = matrixA[0xd] * matrixB[7] + matrixA[9] * matrixB[6] + matrixA[1] * matrixB[4] + matrixA[5] * matrixB[5];
    
    // Calculate element [1][2] of the result matrix (row 1 of lhs dot col 2 of rhs)
    result[6] = matrixA[0xe] * matrixB[7] + matrixA[10] * matrixB[6] + matrixA[2] * matrixB[4] + matrixA[6] * matrixB[5];
    
    // Calculate element [1][3] of the result matrix (row 1 of lhs dot col 3 of rhs)
    result[7] = matrixA[0xf] * matrixB[7] + matrixA[0xb] * matrixB[6] + matrixA[3] * matrixB[4] + matrixA[7] * matrixB[5];
    
    // Calculate element [2][0] of the result matrix (row 2 of lhs dot col 0 of rhs)
    result[8] = matrixA[0xc] * matrixB[0xb] + matrixA[8] * matrixB[10] + *matrixA * matrixB[8] + matrixA[4] * matrixB[9];
    
    // Calculate element [2][1] of the result matrix (row 2 of lhs dot col 1 of rhs)
    result[9] = matrixA[0xd] * matrixB[0xb] + matrixA[9] * matrixB[10] + matrixA[1] * matrixB[8] + matrixA[5] * matrixB[9];
    
    // Calculate element [2][2] of the result matrix (row 2 of lhs dot col 2 of rhs)
    result[10] = matrixA[0xe] * matrixB[0xb] + matrixA[10] * matrixB[10] + matrixA[2] * matrixB[8] + matrixA[6] * matrixB[9];
    
    // Calculate element [2][3] of the result matrix (row 2 of lhs dot col 3 of rhs)
    result[11] = matrixA[0xf] * matrixB[0xb] + matrixA[0xb] * matrixB[10] + matrixA[3] * matrixB[8] + matrixA[7] * matrixB[9];
    
    // Calculate element [3][0] of the result matrix (row 3 of lhs dot col 0 of rhs)
    result[12] = matrixA[0xc] * matrixB[0xf] + matrixA[8] * matrixB[0xe] + *matrixA * matrixB[0xc] + matrixA[4] * matrixB[0xd];
    
    // Calculate element [3][1] of the result matrix (row 3 of lhs dot col 1 of rhs)
    result[13] = matrixA[0xd] * matrixB[0xf] + matrixA[9] * matrixB[0xe] + matrixA[1] * matrixB[0xc] + matrixA[5] * matrixB[0xd];
    
    // Calculate element [3][2] of the result matrix (row 3 of lhs dot col 2 of rhs)
    result[14] = matrixA[0xe] * matrixB[0xf] + matrixA[10] * matrixB[0xe] + matrixA[2] * matrixB[0xc] + matrixA[6] * matrixB[0xd];
    
    // Calculate element [3][3] of the result matrix (row 3 of lhs dot col 3 of rhs)
    result[15] = matrixA[0xf] * matrixB[0xf] + matrixA[0xb] * matrixB[0xe] + matrixA[3] * matrixB[0xc] + matrixA[7] * matrixB[0xd];
}