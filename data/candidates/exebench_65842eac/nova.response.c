void minmax(int *a, int *b, int *c, int *d) {
    if (*a > *d)
        *d = *a;
    if (*a < *c)
        *c = *a;
}