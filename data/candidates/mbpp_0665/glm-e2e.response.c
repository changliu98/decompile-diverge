void func0(int *arr, int n, int *out_arr) {
    int first = arr[0];
    int count = 0;
    int out_idx = 0;
    
    // Count occurrences of the first element
    for (int i = 0; i < n; i++) {
        if (arr[i] == first) {
            count++;
        }
    }
    
    // Copy elements that are not equal to the first element
    for (int i = 0; i < n; i++) {
        if (arr[i] != first) {
            out_arr[out_idx++] = arr[i];
        }
    }
    
    // Append the first element 'count' times at the end
    for (int i = 0; i < count; i++) {
        out_arr[out_idx++] = first;
    }
}