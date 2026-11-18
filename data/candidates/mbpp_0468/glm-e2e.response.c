int func0(int *arr, int n) {
    int temp[n];
    int max_val;

    // Copy elements from arr to temp
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    // Update elements in temp
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && temp[i] < temp[j] * arr[i]) {
                temp[i] = temp[j] * arr[i];
            }
        }
    }

    // Find the maximum value in temp
    max_val = temp[0];
    for (int i = 1; i < n; i++) {
        if (temp[i] > max_val) {
            max_val = temp[i];
        }
    }

    return max_val;
}