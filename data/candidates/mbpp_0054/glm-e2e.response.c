void func0(int *arr, int n) {
    int max = 0;
    int i;
    
    // Find the maximum value
    for (i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    // Allocate count array
    int *count = (int *)malloc((max + 1) * sizeof(int));
    
    // Initialize count array to 0
    int j;
    for (j = 0; j <= max; j++) {
        count[j] = 0;
    }
    
    // Count occurrences of each element
    int k;
    for (k = 0; k < n; k++) {
        count[arr[k]]++;
    }
    
    // Reconstruct the sorted array
    int idx = 0;
    int m;
    for (m = 0; m <= max; m++) {
        int p;
        for (p = 0; p < count[m]; p++) {
            arr[idx] = m;
            idx++;
        }
    }
    
    free(count);
}