int func0(int *arr, int n) {
    int *count = calloc(n + 1, sizeof(int));
    int max_val = -1;
    
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        
        if (count[arr[i]] >= arr[i] && arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    free(count);
    return max_val;
}