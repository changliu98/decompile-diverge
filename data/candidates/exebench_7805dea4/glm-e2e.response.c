void mlVectorMultMatrixTo(const Vector3 *vec, const Matrix4x4 *mat, Vector3 *result) {
    // X component
    result->x = mat->m[0][0] * vec->x + 
                mat->m[1][0] * vec->y + 
                mat->m[2][0] * vec->z + 
                mat->m[3][0];       // implicitly vec->w = 1.0

    // Y component
    result->y = mat->m[0][1] * vec->x + 
                mat->m[1][1] * vec->y + 
                mat->m[2][1] * vec->z + 
                mat->m[3][1];

    // Z component
    result->z = mat->m[0][2] * vec->x + 
                mat->m[1][2] * vec->y + 
                mat->m[2][2] * vec->z + 
                mat->m[3][2];
}