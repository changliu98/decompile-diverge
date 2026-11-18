void matrixApply(Matrix *matrix, float x, float y, float z, float *outx, float *outy, float *outz) {
    *outx = matrix->m11 * x + matrix->m12 * y + matrix->m13 * z + matrix->m14;
    *outy = matrix->m21 * x + matrix->m22 * y + matrix->m23 * z + matrix->m24;
    *outz = matrix->m31 * x + matrix->m32 * y + matrix->m33 * z + matrix->m34;
}