void vector3d_cross(struct Vector3d *a, struct Vector3d *b, struct Vector3d *out) {
    out->x = (a->y * b->z) + -(a->z * b->y);
    out->y = (a->z * b->x) + -(a->x * b->z);
    out->z = (a->x * b->y) + -(a->y * b->x);
}