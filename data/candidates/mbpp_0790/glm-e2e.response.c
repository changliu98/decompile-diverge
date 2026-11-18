bool func0(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != i % 2) {
            return false;
        }
    }
    return true;
}