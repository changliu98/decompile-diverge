void func0(int *a, int *b) {
    int i;
    for (i = 0; i < 4; i++) {
        if (a[i] > b[i] / 2 * 2 * (a[i] > b[i] / 2))
            a[i] -= b[i] / 2 * 2 * (a[i] > b[i] / 2);
    }
}