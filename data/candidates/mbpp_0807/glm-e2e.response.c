int func0(int *arr, int n) {
    int i = 0;
    int result;

    while (i < n) {
        if (arr[i] % 2 != 0) {
            result = arr[i];
            return result;
        }
        i++;
    }
    
    result = -1;
    return result;
}