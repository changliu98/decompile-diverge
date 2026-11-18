void func0(int *a, int *b, int c) {
    int x = a[*b];
    *b = *b - 1;
    int y = a[*b];
    a[*b] = x + y;
}