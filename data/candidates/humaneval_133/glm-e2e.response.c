int func0(float *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int c = (int)ceil(arr[i]);
        sum += c * (int)ceil(arr[i]);
    }
    return sum;
}