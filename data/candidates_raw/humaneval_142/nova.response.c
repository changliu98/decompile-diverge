int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        switch (i % 4) {
        case 0:
            sum += arr[i] * arr[i];
            break;
        case 1:
            sum += arr[i] * arr[i] * arr[i];
            break;
        case 2:
            sum += arr[i];
            break;
        default:
            break;
        }
    }
    return sum;
}