void swap(int *arr) {
    int min_idx = 0;
    int min_val = arr[0];
    
    // Find the index of the minimum element
    for (int i = 0; i < 10; i++) {
        if (arr[i] < min_val) {
            min_idx = i;
        }
    }
    
    int max_idx = 0;
    int max_val = arr[0];
    
    // Find the index of the maximum element
    for (int i = 0; i < 10; i++) {
        if (arr[i] > max_val) {
            max_idx = i;
        }
    }
    
    // Swap the first element (arr[0]) with the minimum element (arr[min_idx])
    // using XOR swap
    arr[0] += arr[min_idx];
    arr[min_idx] = arr[0] - arr[min_idx];
    arr[0] = arr[0] - arr[min_idx];
    
    // Swap the last element (arr[9]) with the maximum element (arr[max_idx])
    // using XOR swap
    arr[9] += arr[max_idx];
    arr[max_idx] = arr[9] - arr[max_idx];
    arr[9] = arr[9] - arr[max_idx];
}