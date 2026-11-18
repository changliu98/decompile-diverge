void vec4Divide(vec4 *result, const vec4 *a, const vec4 *b) {
    result->x = a->x / b->x;
    result->y = a->y / b->y;
    result->z = a->z / b->z;
    result->w = a->w / b->w;
}