int valid(int *arr, int n) {
    for (int i = 0; i < n - 2; i++) {
        if (arr[i] > 0) {
            arr[i + 2] -= arr[i] * 3;
            arr[i + 1] -= arr[i] * 2;
            arr[i] = 0;
        } else if (arr[i] < 0) {
            return 0;
        }
    }

    if (arr[n - 1] == 0 && arr[n - 2] == 0) {
        return 1;
    } else {
        return 0;
    }
}