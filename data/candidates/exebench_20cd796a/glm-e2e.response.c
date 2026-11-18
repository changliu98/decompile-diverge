void cquat_add(struct cquat *res, const struct cquat *a, const struct cquat *b) {
    res->w = a->w + b->w;
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    res->z = a->z + b->z;
}