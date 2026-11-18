void calcula_target(struct Point *a, struct Point *b, struct Point *target) {
    target->x = b->x - a->x + b->x;
    target->y = b->y - a->y + b->y;
}