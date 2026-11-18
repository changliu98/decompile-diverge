int func0(int *arr, int size) {
    int i, sum = 0;
    for (i = 0; i < size; i++) {
        sum = sum * 10 + arr[i];
    }
    return sum;
}