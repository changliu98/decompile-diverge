bool func0(int *arr, int n, int threshold) {
    for (int i = 0; i < n; i++) {
        if (arr[i] >= threshold) {
            return false;
        }
    }
    return true;
}