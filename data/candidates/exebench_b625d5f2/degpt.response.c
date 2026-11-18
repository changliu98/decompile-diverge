void compute_matrix_T(double *result_matrix, double param_a, double param_b, double param_c, double param_d)
{
    // Set the first element of the matrix T to the value of a
    *result_matrix = param_a;
    // Set the second element of the matrix T to the product of a and b
    result_matrix[1] = param_a * param_b;
    // Set the third element of the matrix T to the product of a, d, and a constant DAT_00102008
    result_matrix[2] = constant_factor * param_a * param_d;
    // Set the fourth element of the matrix T to the product of a and the sum of the product of DAT_00102008, b, d and the product of a and c
    result_matrix[3] = param_a * (constant_factor * param_b * param_d + param_a * param_c);
}