void prod_vet(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c) {
    // c->z = a->x * b->y - a->y * b->x
    c->z = a->x * b->y - a->y * b->x;
    
    // c->y = a->z * b->x - a->x * b->z
    c->y = a->z * b->x - a->x * b->z;
    
    // c->x = a->y * b->z - a->z * b->y
    c->x = a->y * b->z - a->z * b->y;
}