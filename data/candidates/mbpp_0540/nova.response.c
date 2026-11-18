int func0(int *arr, int n) {
    int max_so_far = max_subarray(arr, n);
    int min_so_far = 0;
    int max_ending_here = 0;
    int min_ending_here = n;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            max_so_far++;
        } else {
            if (max_ending_here > min_so_far) {
                int temp = max_ending_here;
            } else {
                int temp = min_so_far;
                min_ending_here = max_so_far;
                max_ending_here = temp;
            }
            if (min_ending_here < n) {
                int temp = min_ending_here;
            } else {
                int temp = max_so_far;
            }
            max_so_far = 0;
        }
    }
    return max_ending_here - min_ending_here;
}