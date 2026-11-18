int func0(int *arr, int n) {
    sortArray(arr, n);
    int count = 0;
    int max_len = 0;
    int min_len = n;
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            count++;
        } else {
            if (max_len < count) {
                max_len = count;
            }
            if (min_len > count) {
                min_len = count;
            }
            count = 0;
        }
    }
    
    return max_len - min_len;
}