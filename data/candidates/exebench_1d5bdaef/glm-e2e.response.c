int foo(struct Point *p, int val) {
    if ((p->x > 0.0f) == (p->y > 0.0f)) {
        return val;
    } else {
        return 0;
    }
}