void r3cpsc(struct Vector3 *dest, const struct Vector3 *src, double scalar) {
    dest->x = src->x * scalar;
    dest->y = src->y * scalar;
    dest->z = src->z * scalar;
}