void vec3_cross(vec3 *out, const vec3 *a, const vec3 *b) {
    out->x = (a->y * b->z) + (-(a->z * b->y));
    out->y = (a->z * b->x) + (-(a->x * b->z));
    out->z = (a->x * b->y) + (-(a->y * b->x));
}