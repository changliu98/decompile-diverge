int func0(int *arr, int arrSize) {
    if (arrSize == 0) {
        return -32768;
    }

    int sum = 0;
    int sign = 1;

    for (int i = 0; ; i++) {
        if (i >= arrSize) {
            break;
        }
        sum += abs(arr[i]);
        if (arr[i] == 0) {
            sign *= 0;
        }
        if (arr[i] < 0) {
            sign *= -1;
        }
    }

    return sum * sign;
}