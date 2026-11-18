void mul_mat_vec_2(float *matrix, float *point, float *output)
{
    // Compute the first component of the output vector:
    // o[0] = p[0] * m[0] + p[1] * m[1]
    *output = *point * *matrix + point[1] * matrix[1];

    // Compute the second component of the output vector:
    // o[1] = p[0] * m[2] + p[1] * m[3]
    output[1] = *point * matrix[2] + point[1] * matrix[3];
}