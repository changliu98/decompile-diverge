int func0(int *a, int n) {
    int i, j, k, l, m, max = 0, count = 0;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            int *b = (int *)malloc(n * sizeof(int));
            for (k = 0; k < j; k++) {
                if (a[k]!= a[j])
                    b[k] = a[k];
                else
                    break;
            }
            for (l = k; l < n; l++) {
                if (b[l] == b[l - 1])
                    break;
                b[l] = a[j];
            }
            if (max < l)
                max = l;
            for (m = 0; m < max; m++) {
                if (b[m] == b[m + 1]) {
                    count++;
                    break;
                }
            }
            free(b);
        }
    }
    return count;
}