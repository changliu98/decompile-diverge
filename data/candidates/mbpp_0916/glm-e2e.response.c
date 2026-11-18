bool func0(int *arr, int n, int target, int *result) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == target) {
                    result[0] = arr[i];
                    result[1] = arr[j];
                    result[2] = arr[k];
                    return true;
                }
            }
        }
    }
    return false;
}