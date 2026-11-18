int func0(int *arr, int n) {
    int *dp1 = __builtin_alloca((n + 1) * sizeof(int));
    int *dp2 = __builtin_alloca((n + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        dp1[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp1[i] < dp1[j] + 1) {
                dp1[i] = dp1[j] + 1;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        dp2[i] = 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dp2[i] < dp2[j] + 1) {
                dp2[i] = dp2[j] + 1;
            }
        }
    }

    int max_len = dp1[0] + dp2[0] - 1;
    for (int i = 1; i < n; i++) {
        if (dp1[i] + dp2[i] - 1 > max_len) {
            max_len = dp1[i] + dp2[i] - 1;
        }
    }

    return max_len;
}