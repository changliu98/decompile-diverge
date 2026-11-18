void minmax(int *a, int b, int *min, int *max) {
    if (*a < *min) {
        *min = *a;
    }
    if (*a > *max) {
        *max = *a;
    }
}