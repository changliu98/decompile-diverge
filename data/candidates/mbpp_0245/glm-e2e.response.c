int func0(int *arr, int n) {
    int *dp1 = (int *)alloca(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp1[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp1[i] < dp1[j] + arr[i]) {
                dp1[i] = dp1[j] + arr[i];
            }
        }
    }

    int *dp2 = (int *)alloca(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp2[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[n - i - 1] > arr[n - j - 1] && dp2[n - i - 1] < dp2[n - j - 1] + arr[n - i - 1]) {
                dp2[n - i - 1] = dp2[n - j - 1] + arr[n - i - 1];
            }
        }
    }

    int max_val = 0xfa0a1f01; // -100000000 in signed 32-bit integer
    for (int i = 0; i < n; i++) {
        if (dp1[i] + dp2[i] - arr[i] > max_val) {
            max_val = dp1[i] + dp2[i] - arr[i];
        }
    }

    return max_val;
}