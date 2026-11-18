void func0(int *a, int n, int *max) {
    int max1 = 0, max2 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0 && (max1 == 0 || a[i] > max1))
            max1 = a[i];
        if (a[i] < 0 && (max2 == 0 || a[i] < max2))
            max2 = a[i];
    }
    max[0] = max1;
    max[1] = max2;
}