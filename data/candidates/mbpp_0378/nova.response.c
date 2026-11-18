void func0(int *arr, int n, int *brr) {
    int i;
    *brr = arr[n - 1];
    int flag = 1;
    for (i = arr[2]; flag; i++) {
        if (i < n) {
            *(brr + i) = arr[i - 1];
        } else {
            break;
        }
    }
}