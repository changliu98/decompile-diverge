int func0(int *arr, int n, int threshold) {
    int i;
    char result;
    
    for (i = 0; i < n; i++) {
        if (arr[i] < threshold) {
            result = 0;
            return result & 1;
        }
    }
    result = 1;
    return result & 1;
}