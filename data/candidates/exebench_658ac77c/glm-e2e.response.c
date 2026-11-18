void vertexAdd(const struct Vertex *a, const struct Vertex *b, struct Vertex *result) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}