int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0;; i++) {
        if (i < n) {
            sum += arr[i];
        } else {
            break;
        }
    }
    return sum;
}