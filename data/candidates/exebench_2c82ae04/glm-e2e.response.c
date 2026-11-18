float vec3f_dot(struct vec3f *a, struct vec3f *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}