void summary(int *arr, int n, double *pos_ratio, double *neg_ratio, double *zero_ratio) {
    int pos_count = 0;
    int neg_count = 0;
    int zero_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            pos_count++;
        } else if (arr[i] < 0) {
            neg_count++;
        } else {
            zero_count++;
        }
    }
    
    *pos_ratio = (double)pos_count / (double)n;
    *neg_ratio = (double)neg_count / (double)n;
    *zero_ratio = (double)zero_count / (double)n;
}