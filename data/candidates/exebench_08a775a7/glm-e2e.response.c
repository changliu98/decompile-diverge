int next(int *arr, int size) {
    int i = 0;
    
    // Loop to skip all leading elements that are non-zero
    while (i < size && arr[i] != 0) {
        arr[i] = 0;
        i++;
    }
    
    // If we haven't reached the end, set the current element to 1 and return 1
    if (i < size) {
        arr[i] = 1;
        return 1;
    }
    
    // If we reached the end, return 0
    return 0;
}