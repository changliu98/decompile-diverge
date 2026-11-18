int func0(int *arr, int n) {
    int buf[n];
    for (int i = 0; i < n; i++) {
        buf[i] = 1;
    }
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < j; k++) {
            if (arr[j] == arr[k] + 1 || arr[j] == arr[k] - 1) {
                if (buf[j] < buf[k] + 1) {
                    buf[j] = buf[k] + 1;
                }
            }
        }
    }
    int max = 1;
    for (int i = 0; i < n; i++) {
        if (max < buf[i]) {
            max = buf[i];
        }
    }
    return max;
}