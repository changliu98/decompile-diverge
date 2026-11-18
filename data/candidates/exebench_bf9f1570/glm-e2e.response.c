void Mat4_vec3_mul_inv(vec3 *out, const mat4 *m, const vec3 *v) {
    float x = v->x * m->m[0][0] + v->y * m->m[0][1] + v->z * m->m[0][2];
    float y = v->x * m->m[1][0] + v->y * m->m[1][1] + v->z * m->m[1][2];
    float z = v->x * m->m[2][0] + v->y * m->m[2][1] + v->z * m->m[2][2];

    float w = m->m[3][0] + m->m[3][1] + m->m[3][2];

    out->x = x - w;
    out->y = y - w;
    out->z = z - w;
}