bool func0(int *arr, int n) {
    int max_val = -2147483648; // 0x80000000
    for (int i = 1; i < n; i++) {
        if (max_val > arr[i]) {
            return false;
        }
        if (arr[i - 1] > max_val) {
            max_val = arr[i - 1];
        }
    }
    return true;
}