void cquat_sub(struct quat *dst, const struct quat *a, const struct quat *b) {
    dst->w = a->w - b->w;
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
    dst->z = a->z - b->z;
}