struct Result max1D_double(double *arr, int n, struct Result *res) {
    res->max_idx = 0;
    res->max_val = arr[0];
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > res->max_val) {
            res->max_val = arr[i];
            res->max_idx = i;
        }
    }
    
    return *res;
}