int sumOfFirstOddAndEven(int *arr, int size) {
    int first_even = -1, first_odd = -1;
    for (int i = 0; ; i++) {
        if (i >= size) break;
        if (arr[i] % 2 == 0) {
            first_even = arr[i];
            break;
        }
    }
    for (int i = 0; ; i++) {
        if (i >= size) break;
        if (arr[i] % 2 != 0) {
            first_odd = arr[i];
            break;
        }
    }
    return first_even + first_odd;
}