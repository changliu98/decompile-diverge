void func0(int *a, int *b) {
    if (*a > *b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}