void vec3CrossProduct(struct vec3 *result, const struct vec3 *a, const struct vec3 *b) {
    result->x = (a->y * b->z) + (-(a->z * b->y));
    result->y = (a->z * b->x) + (-(a->x * b->z));
    result->z = (a->x * b->y) + (-(a->y * b->x));
}