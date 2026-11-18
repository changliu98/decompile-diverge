void Vec3Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *result) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}