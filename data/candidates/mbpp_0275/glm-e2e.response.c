int func0(int *arr, int n, int divisor) {
    // First loop: adjust array elements based on the divisor
    for (int i = 0; i < n; i++) {
        int quotient = arr[i] / divisor;
        int remainder = arr[i] % divisor;
        arr[i] = quotient + (remainder != 0);
    }

    // Second loop: find the index of the maximum element in the modified array
    int max_idx = -1;
    int max_val = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (max_val < arr[i]) {
            max_val = arr[i];
            max_idx = i;
        }
    }

    return max_idx + 1;
}