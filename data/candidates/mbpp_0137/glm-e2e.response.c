double func0(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            count++;
        }
    }
    double ratio = (double)count / (double)n;
    ratio = round(ratio * 100.0) / 100.0;
    return ratio;
}