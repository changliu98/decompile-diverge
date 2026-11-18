int func0(int *arr, int n) {
    int i;
    int result;
    
    for (i = 0; i < n; i++) {
        if (arr[i] == i) {
            result = i;
            return result;
        }
    }
    
    result = -1;
    return result;
}