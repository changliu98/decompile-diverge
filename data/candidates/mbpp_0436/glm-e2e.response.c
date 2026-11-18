int func0(int *arr, int n) {
    int i = 0;
    int result = 0;
    
    while (i < n) {
        if (arr[i] < 0) {
            result = arr[i];
            break;
        }
        i++;
    }
    
    return result;
}