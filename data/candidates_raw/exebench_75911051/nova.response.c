int func0(int a, int b, int *r) {
    int q = a / b;
    *r = a % b;
    return q;
}