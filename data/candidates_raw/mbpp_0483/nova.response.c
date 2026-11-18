int func0(int n) {
    int i, j, k, l, m, p;
    i = 1;
    j = 1;
    while (1) {
        i = 1;
        while (i < n) {
            i *= j;
            if (i % n == 0) {
                p = i;
                goto L1;
            }
        }
        j++;
    }
L1:
    return p;
}