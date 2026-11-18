double func0(int *arr, int size) {
    int first_even = -1, first_odd = -1;
    double result;

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            first_even = arr[i];
            break;
        }
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            first_odd = arr[i];
            break;
        }
    }

    if (first_even != -1 && first_odd != -1)
        result = (double) first_even / first_odd;
    else
        result = -1;

    return result;
}