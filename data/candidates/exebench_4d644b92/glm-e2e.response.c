int twiddle1(int *a, int *b) {
    *a = *a + *b;
    *a = *a + *b;
    return *a;
}