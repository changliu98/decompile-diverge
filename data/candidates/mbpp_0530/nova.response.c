double func0(int *arr, int size) {
    int i, sum = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] > 0) {
            sum++;
        }
    }
    double avg = sum / (double)size;
    return round(avg * 100) / 100.0;
}