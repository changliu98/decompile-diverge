int func0(int *arr, int n) {
    int max_sum = 0x80000000; // -2147483648
    int current_sum = 0;
    int end_idx = 0;
    int max_end_idx = 0;
    int start_idx = 0;
    int i = 0;

    for (; i < n; i++) {
        current_sum += arr[i];
        
        if (max_sum < current_sum) {
            max_sum = current_sum;
            end_idx = start_idx;
            max_end_idx = i;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
            start_idx = i + 1;
        }
    }
    
    return max_end_idx - end_idx + 1;
}