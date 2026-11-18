bool func0(int *arr, int n) {
    int size = n - 1;
    int diffs[size];
    
    for (int i = 1; i < n; i++) {
        diffs[i - 1] = arr[i] - arr[i - 1];
    }
    
    for (int i = 1; i < n - 1; i++) {
        if (diffs[i] != diffs[0]) {
            return false;
        }
    }
    
    return true;
}