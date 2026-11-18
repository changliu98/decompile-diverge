int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0;; i++) {
        if (i * 2 >= n)
            break;
        if (arr[i * 2] % 2 == 1)
            sum += arr[i * 2];
    }
    return sum;
}