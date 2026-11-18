void func0(int *arr, int n, int *out) {
    int min_neg = 0;
    int max_pos = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (min_neg == 0 || arr[i] > min_neg) {
                min_neg = arr[i];
            }
        }
        
        if (arr[i] > 0) {
            if (max_pos == 0 || arr[i] < max_pos) {
                max_pos = arr[i];
            }
        }
    }
    
    out[0] = min_neg;
    out[1] = max_pos;
}