int func0(int *a, int *b) {
    int *t;
    while (*a > 0) {
        if (*a < *b) {
            t = a;
            a = b;
            b = t;
        }
        *a = *a - *b;
    }
    return *b;
}