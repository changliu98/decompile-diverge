int getPossibleCount(int *a, int *b) {
    int i, j, k = 0, n = 9;
    for (i = 0; i < n; i++) {
        if (a[i]!= 0) {
            k++;
            *b = a[i];
        }
    }
    return k;
}