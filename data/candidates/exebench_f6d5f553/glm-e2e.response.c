float vector3d_dot(const vector3d *a, const vector3d *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}