int func0(int *arr, int n) {
    int i, j, k;
    int *tmp = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        tmp[i] = arr[i];
    }
    int max = -1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (tmp[i] > tmp[j] && tmp[i] < tmp[i] + tmp[j]) {
                tmp[i] = tmp[j] + tmp[i];
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (tmp[i] - tmp[j] > max) {
                max = tmp[i] - tmp[j];
            }
        }
    }
    return max;
}