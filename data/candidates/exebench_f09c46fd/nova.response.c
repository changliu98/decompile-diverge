void minmax(int *a, int n, int *min, int *max) {
    if (*min > *a)
        *min = *a;
    if (*max < *a)
        *max = *a;
}