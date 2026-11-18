void f(int *a, int *b) {
    if (*a > *b) {
        int *c = a;
        *a = *b;
        *b = *c / 2;
    } else {
        *a *= 2;
        int *c = b;
        *b = *c / 2;
    }
}