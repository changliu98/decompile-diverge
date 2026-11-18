long long func0(float *arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(arr[i] - round(arr[i])) <= pow(10, -6)) {
            sum += (int)round(arr[i]) * (int)round(arr[i]);
        }
    }
    return sum;
}