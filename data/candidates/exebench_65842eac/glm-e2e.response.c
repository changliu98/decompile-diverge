void minmax(int *val, int *min, int *max) {
    if (*val < *min) {
        *min = *val;
    }
    if (*val > *max) {
        *max = *val;
    }
}