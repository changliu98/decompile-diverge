void adjust_point(int *p) {
    if (*p < 0) {
        *p = 0;
    } else if (*p > 100) {
        *p = 100;
    }
}