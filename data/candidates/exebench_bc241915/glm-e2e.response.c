void fb_hSetDirty(int *min_ptr, int *max_ptr, int min_val, int max_val) {
    if (*min_ptr == *max_ptr) {
        *min_ptr = min_val;
        *max_ptr = max_val;
    } else {
        if (min_val < *min_ptr) {
            *min_ptr = min_val;
        }
        if (max_val > *max_ptr) {
            *max_ptr = max_val;
        }
    }
}