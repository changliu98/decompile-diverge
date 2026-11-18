void func0(int *a, int *b) {
    int i;
    for (i = 0; i < 4; i++) {
        a[i] = a[i] % b[i];
        if (a[i] < b[i])
            a[i] += b[i];
    }
}