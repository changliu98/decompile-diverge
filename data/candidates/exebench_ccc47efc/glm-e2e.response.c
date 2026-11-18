double determinant_3x3(float *matrix) {
    double det = 0.0;
    double temp[3][3];

    // Zero out the temp array (72 bytes = 3x3 * sizeof(double))
    memset(temp, 0, 72);

    // Convert the 3x3 float matrix to a 3x3 double matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = (double)matrix[j * 3 + i];
        }
    }

    // Calculate the determinant using the Rule of Sarrus
    // Note: The memory layout and indexing indicate column-major access
    // temp[0][0], temp[1][1], temp[2][2]
    det = temp[0][0] * (temp[1][1] * temp[2][2] - temp[1][2] * temp[2][1]);
    
    // temp[0][1], temp[1][2], temp[2][0]
    det += temp[0][1] * (temp[1][2] * temp[2][0] - temp[1][0] * temp[2][2]);
    
    // temp[0][2], temp[1][0], temp[2][1]
    det += temp[0][2] * (temp[1][0] * temp[2][1] - temp[1][1] * temp[2][0]);

    return det;
}