// Computes an inverse rotation matrix approximation for fixed-point arithmetic.
// Returns 1 if the input matrix m is invalid (singular or degenerate), 0 otherwise.
// The result is stored in the output array o, which must be at least 6 elements long.
int _inverse_rot(int *input_matrix, int *output_matrix)
{
    // Check for division by zero or degenerate case where rotation components are zero.
    // m[1] and m[2] correspond to sine and cosine components in a 2D rotation matrix.
    if ((input_matrix[1] == 0) || (input_matrix[2] == 0)) {
        return 1;
    }
    // Initialize output array to zero.
    *output_matrix = 0;
    // Compute fixed-point reciprocal of m[2] (cosine) scaled by 0x100000.
    output_matrix[1] = (int)(0x100000 / (long)input_matrix[2]);
    // Compute fixed-point reciprocal of m[1] (sine) scaled by 0x100000.
    output_matrix[2] = (int)(0x100000 / (long)input_matrix[1]);
    // Set o[3] to zero as it is not used in this simplified inverse.
    output_matrix[3] = 0;
    // Compute translation component o[4] using m[5] and precomputed o[2].
    output_matrix[4] = -(input_matrix[5] * output_matrix[2]) / 0x400;
    // Compute translation component o[5] using m[4] and precomputed o[1].
    output_matrix[5] = -(input_matrix[4] * output_matrix[1]) / 0x400;
    // Return success.
    return 0;
}