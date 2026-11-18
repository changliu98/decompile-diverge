void func0(int *a, int *b) {
    int i;
    for (i = 0; i < 4; i++) {
        a[i] -= (b[i] > a[i]) * 2 * b[i];
    }
}