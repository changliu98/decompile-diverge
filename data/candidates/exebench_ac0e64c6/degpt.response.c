// Adds scaled matrix b to matrix a and stores the result in out
// out[i] = a[i] + b[i] * c for all 16 elements of the 4x4 matrices
void warp_mat4_add_scaled(float *result, float *matrix_a, float *matrix_b, float scale_factor)
{
    for (int i = 0; i < 16; i++) {
        result[i] = matrix_b[i] * scale_factor + matrix_a[i];
    }
}