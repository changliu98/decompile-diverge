void func0(int *a, int n) {
    int i, j = -1;
    for (i = 0; i < n; i++) {
        if (j < 0) {
            if (a[i] < 0 && a[j] >= 0) {
                j = i;
            }
        } else {
            if (a[i] >= 0 && a[j] < 0) {
                reverse(a, n, j, i - 1);
                if (i - j > 2)
                    j = j + 2;
                else
                    j = -1;
            }
        }
    }
}