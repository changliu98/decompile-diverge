void f(int *a, int *b) {
    if (*a > *b) {
        *a = *a / 2;
        *b = *b * 2;
    } else {
        *a = *a * 2;
        *b = *b / 2;
    }
}