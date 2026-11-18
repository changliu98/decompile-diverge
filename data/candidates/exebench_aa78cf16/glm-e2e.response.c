void vdiff(struct Vec3 *out, const struct Vec3 *a, const struct Vec3 *b) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}