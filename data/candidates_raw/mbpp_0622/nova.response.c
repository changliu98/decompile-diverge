float func0(int *a, int *b, int n) {
    int i = 0, j = 0, max = -1, min = -1;
    for (int k = 0; k < n + 1; k++) {
        if (i == n) {
            min = min;
            max = b[j];
            j++;
            continue;
        }
        if (j == n) {
            min = a[i];
            max = max;
            i++;
            continue;
        }
        if (a[i] <= b[j]) {
            min = a[i];
            max = a[i];
            i++;
        } else {
            min = b[j];
            max = b[j];
            j++;
        }
    }
    return (float)(min + max) / 2;
}