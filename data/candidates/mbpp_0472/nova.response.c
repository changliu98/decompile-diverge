bool func0(int *arr, int n) {
    int *tmp = (int *)malloc(n * sizeof(int));
    int i, j, k;
    for (i = 0; i < n; i++) {
        tmp[i] = arr[i];
    }
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (tmp[i] > tmp[j]) {
                int t = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = t;
            }
        }
    }
    bool flag = true;
    for (k = 1; k < n; k++) {
        if (tmp[k]!= tmp[k - 1] + 1) {
            flag = false;
            break;
        }
    }
    free(tmp);
    return flag;
}