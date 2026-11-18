void geom_cross3f(const vec3 *a, const vec3 *b, vec3 *out) {
    // out->x = a->y * b->z - a->z * b->y
    float term1 = a->y * b->z;
    float term2 = a->z * b->y;
    uint32_t term2_bits = *(uint32_t*)&term2 ^ 0x80000000;
    float neg_term2 = *(float*)&term2_bits;
    out->x = term1 + neg_term2;

    // out->y = a->z * b->x - a->x * b->z
    term1 = a->z * b->x;
    term2 = a->x * b->z;
    term2_bits = *(uint32_t*)&term2 ^ 0x80000000;
    neg_term2 = *(float*)&term2_bits;
    out->y = term1 + neg_term2;

    // out->z = a->x * b->y - a->y * b->x
    term1 = a->x * b->y;
    term2 = a->y * b->x;
    term2_bits = *(uint32_t*)&term2 ^ 0x80000000;
    neg_term2 = *(float*)&term2_bits;
    out->z = term1 + neg_term2;
}