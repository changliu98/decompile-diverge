void Mat4_Translate(float *matrix, float *translation_vector)
{
    // Update the translation components (column 3) of the 4x4 matrix
    // by adding the product of the rotation/scale columns and the translation vector
    matrix[0xc] = matrix[8] * translation_vector[2] + matrix[0] * translation_vector[0] + matrix[4] * translation_vector[1] + matrix[0xc];
    matrix[0xd] = matrix[9] * translation_vector[2] + matrix[1] * translation_vector[0] + matrix[5] * translation_vector[1] + matrix[0xd];
    matrix[0xe] = matrix[10] * translation_vector[2] + matrix[2] * translation_vector[0] + matrix[6] * translation_vector[1] + matrix[0xe];
}