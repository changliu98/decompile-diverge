void Mat4_vec3_mul(struct Vector3 *v, const Mat4 *m, const struct Vector3 *src)
{
    float x = m->m00 * src->x + m->m10 * src->y + m->m20 * src->z + m->m30;
    float y = m->m01 * src->x + m->m11 * src->y + m->m21 * src->z + m->m31;
    float z = m->m02 * src->x + m->m12 * src->y + m->m22 * src->z + m->m32;
    v->x = x;
    v->y = y;
    v->z = z;
}