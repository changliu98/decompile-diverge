void myGlMultMatrix(float *matrixA, float *matrixB, float *resultMatrix)
{
    int rowIndex, colIndex;
    // Iterate over rows of the result matrix
    for (rowIndex = 0; rowIndex < 4; rowIndex++) {
        // Iterate over columns of the result matrix
        for (colIndex = 0; colIndex < 4; colIndex++) {
            // Compute element at row i, column j of the product matrix a * b
            // Note: The indexing pattern suggests column-major storage with a specific permutation
            // equivalent to standard matrix multiplication where a and b are 4x4 matrices
            resultMatrix[rowIndex * 4 + colIndex] =
                matrixA[rowIndex * 4 + 3] * matrixB[colIndex + 12] +  // Row 3 of a * Column 3 of b
                matrixA[rowIndex * 4 + 2] * matrixB[colIndex + 8] +   // Row 2 of a * Column 2 of b
                matrixA[rowIndex * 4] * matrixB[colIndex] +           // Row 0 of a * Column 0 of b
                matrixA[rowIndex * 4 + 1] * matrixB[colIndex + 4];    // Row 1 of a * Column 1 of b
        }
    }
}