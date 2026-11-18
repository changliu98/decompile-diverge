int func0(int *a, int b) {
    int c = b;
    *a += b;
    b += c;
    return b + c;
}