int int2arr(int *arr, int num) {
    int i = 0;
    while (num != 0) {
        arr[i] = num % 10;
        num = num / 10;
        i++;
    }
    return i;
}