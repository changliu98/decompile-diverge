void vec3_add(struct vec3 *result, const struct vec3 *a, const struct vec3 *b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}