int func0(int n) {
    int *arr = malloc(n * sizeof(int));
    int **a = malloc((n + 1) * sizeof(int *));
    int **b = malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        a[i] = calloc(3, sizeof(int));
        b[i] = calloc(3, sizeof(int));
    }

    a[0][0] = 0;
    a[0][1] = 0;
    a[0][2] = 0;
    b[0][0] = 0;
    b[0][1] = 0;
    b[0][2] = 0;

    for (int i = 1; i <= n; i++) {
        arr[i - 1] = (i * i - i + 1) % 3;
        for (int j = 0; j < 3; j++) {
            a[i][j] = a[i - 1][j];
        }
        a[i][arr[i - 1]]++;
    }

    for (int k = 1; k < 3; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                b[i][j] = b[i - 1][j];
            }
            if (i >= 1) {
                for (int j = 0; j <= 2; j++) {
                    int val = a[i - 1][j];
                    int *ptr = b[i];
                    int idx = (arr[i - 1] + j) % 3;
                    ptr[idx] += val;
                }
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                a[i][j] = b[i][j];
                b[i][j] = 0;
            }
        }
    }

    int ret = a[n][0];

    for (int i = 0; i <= n; i++) {
        free(a[i]);
        free(b[i]);
    }
    free(a);
    free(b);
    free(arr);

    return ret;
}