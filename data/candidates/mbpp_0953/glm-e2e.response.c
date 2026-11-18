int func0(int *arr, int n) {
    int max_len = 0;
    
    // Bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    // Find the maximum length of consecutive elements
    for (int i = 0; i < n; i++) {
        int current_len = 1;
        while (i + 1 < n && arr[i] == arr[i + 1]) {
            current_len++;
            i++;
        }
        if (current_len > max_len) {
            max_len = current_len;
        }
    }
    
    return max_len;
}