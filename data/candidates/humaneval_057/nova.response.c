int func0(float *a, int n) {
    int i, j, k, l;
    i = j = k = l = 0;
    while (1) {
        if (i < n) {
            if (a[i] > a[i - 1])
                k = 1;
            if (a[i] > a[i + 1])
                l = 1;
        }
        i++;
        if (i == n) {
            if (j == 2)
                return 0;
            else
                return 1;
        }
    }
}