void Mat4_vec3_mul(Vec3 *out, const Mat4 *mat, const Vec3 *vec) {
    float x = mat->m[0][0] * vec->x + mat->m[0][1] * vec->y + mat->m[0][2] * vec->z + mat->m[0][3];
    float y = mat->m[1][0] * vec->x + mat->m[1][1] * vec->y + mat->m[1][2] * vec->z + mat->m[1][3];
    float z = mat->m[2][0] * vec->x + mat->m[2][1] * vec->y + mat->m[2][2] * vec->z + mat->m[2][3];

    out->x = x;
    out->y = y;
    out->z = z;
}