void findMinMax(long *arr, long *min, long *max) {
    for (int i = 1; i < 5; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}