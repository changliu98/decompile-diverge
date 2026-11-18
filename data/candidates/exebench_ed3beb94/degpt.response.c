// Copies 16 float values from the source matrix to the destination matrix
void math_matrix_copy(float *source, float *destination)
{
    // Iterate through each element of the 4x4 matrix (16 elements total)
    for (int i = 0; i < 0x10; i++) {
        // Copy the value from the source to the destination
        destination[i] = source[i];
    }
}