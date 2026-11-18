void shiftarray(int *arr) {
    for (int i = 0; i < 9; i++) {
        arr[i] = arr[i + 1];
    }
    arr[9] = -1;
}