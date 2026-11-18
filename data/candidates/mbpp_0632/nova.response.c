void func0(int *a, int n, int *b) {
    int i, j, k;
    i = j = k = 0;
    while (i < n) {
        if (a[i] == 0) {
            i++;
            j++;
        } else {
            b[j] = a[i];
            j++;
        }
        i++;
    }
    for (i = 0; i < j; i++) {
        b[j] = 0;
        j++;
    }
}