long long func0(long long a[], int n) {
    long long max, min;
    max = min = a[0];
    int i = 1;
    while (i < n + 1) {
        if (max < a[i]) {
            max = a[i] + max;
        } else {
            max = a[i];
        }
        if (min > max) {
            min = max;
        }
        i++;
    }
    return min;
}