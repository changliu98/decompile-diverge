int func0(const void *a, const void *b, const void *c) {
    unsigned long long x = *(unsigned long long *)a;
    unsigned long long y = *(unsigned long long *)b;
    unsigned long long *z;
    if (c)
        z = (unsigned long long *)c;
    else
        z = &y;
    *z = x + y;
    return (x + y) & 1;
}