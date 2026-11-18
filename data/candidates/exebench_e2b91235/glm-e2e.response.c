int num_to_array(int *arr, int num) {
    int i = 0;
    while (num > 0) {
        int digit = num % 10;
        arr[i++] = digit;
        num /= 10;
    }
    return i;
}