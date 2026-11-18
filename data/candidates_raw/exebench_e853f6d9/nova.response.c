int func0(int *a, int *b) {
    int c = *a? 1 : 0;
    *b += *a;
    *a -= 1;
    c = func0(a, b)? 1 : 0;
    return c % 2;
}