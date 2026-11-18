int getPossibleCount(int *arr, int *out) {
    int count = 0;
    int n = 9;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            count++;
            *out = arr[i];
        }
    }
    
    return count;
}