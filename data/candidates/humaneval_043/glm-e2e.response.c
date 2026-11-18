bool func0(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == 0) {
                return true;
            }
        }
    }
    return false;
}