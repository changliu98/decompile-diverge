void vector3d_add(struct Vector3d *a, struct Vector3d *b, struct Vector3d *result) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}