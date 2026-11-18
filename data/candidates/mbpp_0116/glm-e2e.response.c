int func0(int *arr, int n) {
    int result = 0;
    int i = 0;
    while (i < n) {
        result = result * 10 + arr[i];
        i++;
    }
    return result;
}