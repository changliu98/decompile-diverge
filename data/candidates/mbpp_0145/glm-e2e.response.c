int func0(int *arr, int size) {
    int min_val = arr[0];
    int max_val = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    return max_val - min_val;
}