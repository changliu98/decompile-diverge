void func0(int *a, int n, int *max1, int *max2) {
    int i, j;
    if (n < 3) {
        *max1 = *max2 = 0;
        return;
    }
    *max1 = a[0];
    *max2 = a[1];
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] * a[j] > *max1 * *max2) {
                *max1 = a[i];
                *max2 = a[j];
            }
        }
    }
}