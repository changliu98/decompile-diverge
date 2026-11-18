void func0(int *arr, int n, int *out1, int *out2) {
    if (n < 2) {
        *out1 = 0;
        *out2 = 0;
    } else {
        *out1 = arr[0];
        *out2 = arr[1];
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] * arr[j] > *out1 * *out2) {
                    *out1 = arr[i];
                    *out2 = arr[j];
                }
            }
        }
    }
}