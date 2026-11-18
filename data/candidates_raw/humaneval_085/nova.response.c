int func0(int *arr, int n) {
    int sum = 0;
    int i = 0;
    while (1) {
        if (2 * i + 2 > n) {
            break;
        }
        if (arr[2 * i + 1] % 2 == 0) {
            sum += arr[2 * i + 1];
        }
        i++;
    }
    return sum;
}