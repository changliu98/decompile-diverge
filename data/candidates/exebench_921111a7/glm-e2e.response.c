void Vec3Cross(const Vec3 *a, const Vec3 *b, Vec3 *out) {
    // X component: a->y * b->z - a->z * b->y
    out->x = a->y * b->z - a->z * b->y;

    // Y component: a->z * b->x - a->x * b->z
    out->y = a->z * b->x - a->x * b->z;

    // Z component: a->x * b->y - a->y * b->x
    out->z = a->x * b->y - a->y * b->x;
}