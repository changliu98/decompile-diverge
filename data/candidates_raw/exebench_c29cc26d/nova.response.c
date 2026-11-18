__attribute__((noinline, noclone)) struct S func0(struct S x, struct S y) {
    do
        x.ptr[0] = y.ptr[0];
    while (0);
    int u = x.ptr[0];
    int v = y.ptr[0];
    return x;
}