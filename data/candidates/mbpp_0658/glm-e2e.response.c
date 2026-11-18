int func0(int *arr, int n) {
    int max_count = 0;
    int max_item = arr[0];
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            max_item = arr[i];
        }
    }
    
    return max_item;
}