void matrix_swap_rows(float *matrix) {
 float temp;
 temp = matrix[2];
 matrix[2] = matrix[6];
 matrix[6] = matrix[8];
 matrix[8] = matrix[12];
 matrix[12] = matrix[14];
 matrix[14] = matrix[16];
 matrix[16] = matrix[18];
 matrix[18] = temp;
}