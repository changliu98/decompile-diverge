int func0(int *arr, int n) {
    int total_sum = 0;
    int i;
    int prefix_sum = 0;
    int j;
    int pivot_index = -1;

    // Calculate the total sum of the array
    for (i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    // Find the pivot index where left sum equals right sum
    for (j = 0; j < n; j++) {
        total_sum -= arr[j];
        
        if (prefix_sum == total_sum) {
            pivot_index = j;
            return pivot_index;
        }
        
        prefix_sum += arr[j];
    }

    return -1;
}