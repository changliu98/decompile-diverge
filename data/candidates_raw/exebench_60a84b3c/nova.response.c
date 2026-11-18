int func0(int *a, int *b, int *c, int *d, int e, int f) {
    if (*a < e)
        *a = e;
    if (*b < f)
        *b = f;
    if (*a >= *c)
        *a = *c - 1;
    if (*b >= *d)
        *b = *d - 1;
    if (*c <= e)
        *c = e + 1;
    if (*d <= f)
        *d = f + 1;
    if (*c > *a)
        *c = *a;
    if (*d > *b)
        *d = *b;
    return (*c > *a && *d > *b)? 1 : 0;
}