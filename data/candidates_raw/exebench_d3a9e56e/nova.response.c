void func0(int *a) {
    int i, t;
    for (i = 0; i < 5; i++) {
        t = a[i];
        a[i] = a[9 - i];
        a[9 - i] = t;
    }
}