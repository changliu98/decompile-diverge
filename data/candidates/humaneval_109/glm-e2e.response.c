bool func0(int *arr, int n) {
    int count = 0;
    
    if (n == 0) {
        return true;
    }
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            count++;
        }
    }
    
    if (arr[n - 1] > arr[0]) {
        count++;
    }
    
    if (count < 2) {
        return true;
    }
    
    return false;
}