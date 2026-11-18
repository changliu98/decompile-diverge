void func0(int *arr, int n, int exponent, int *out) {
    for (int i = 0; i < n; i++) {
        out[i] = (int)pow((double)arr[i], (double)exponent);
    }
}