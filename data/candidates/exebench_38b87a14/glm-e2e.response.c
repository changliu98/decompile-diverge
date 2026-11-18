void vec3Add(struct Vec3 *result, const struct Vec3 *a, const struct Vec3 *b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}