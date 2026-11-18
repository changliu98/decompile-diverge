int func0(int *a, int *b) {
    int c;
    if (*a == 0) {
        c = *b;
    } else {
        c = a[0] % 10;
        if (c >= b[0])
            *b = a[0];
        *a = a[0] / 10;
    }
    func0(a, b);
    return c;
}