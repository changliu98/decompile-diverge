int func0(int *arr, unsigned long n) {
    int i = 0;
    int result;
    
    while (i < n) {
        if (arr[i] >= 0) {
            result = arr[i];
            return result;
        }
        i++;
    }
    
    return -1;
}