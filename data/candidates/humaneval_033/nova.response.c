void func0(int *arr, int n, int *res) {
    int *tmp = (int *)malloc(sizeof(int) * (n / 3 + 1));
    int i = 0, j = 0, k;
    while (i < n) {
        while (j < n / 3) {
            if (arr[i] < tmp[j]) {
                k = j;
                j = i + 1;
                while (i < j) {
                    if (tmp[i] < tmp[j]) {
                        k = i;
                    }
                    i++;
                }
                if (k!= j) {
                    int t = tmp[j];
                    tmp[j] = tmp[k];
                    tmp[k] = t;
                }
            } else {
                j++;
            }
        }
        if (i % 3 == 0) {
            res[i / 3] = tmp[j];
        } else {
            res[i] = arr[i];
        }
    }
    free(tmp);
}