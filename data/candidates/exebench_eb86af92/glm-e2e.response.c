void maxind(double *arr, int n, double *max_val, double *max_ind) {
    int i = 0;
    
    // Initialize max_val with the first element
    *max_val = arr[0];
    
    // Initialize max_ind to 0.0
    *max_ind = 0.0;
    
    // Loop from i = 1 to n - 1
    for (i = 1; i < n; i++) {
        if (arr[i] > *max_val) {
            *max_val = arr[i];
            *max_ind = (double)i;
        }
    }
}