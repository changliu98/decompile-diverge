int slevmar_box_check(float *lower, float *upper, int n) {
    if (lower == 0 || upper == 0) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (lower[i] > upper[i]) {
            return 0;
        }
    }
    
    return 1;
}