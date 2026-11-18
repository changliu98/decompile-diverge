void Mat4_vec3_mul_T(struct Vector3 *dst, const struct Matrix4 *src, const struct Vector3 *v)
{
    float x = v->x, y = v->y, z = v->z;

    dst->x = src->m00 * x + src->m10 * y + src->m20 * z + src->m30;
    dst->y = src->m01 * x + src->m11 * y + src->m21 * z + src->m31;
    dst->z = src->m02 * x + src->m12 * y + src->m22 * z + src->m32;
}