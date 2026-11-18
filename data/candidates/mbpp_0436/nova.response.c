int func0(int *arr, int size) {
    int i, max;
    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            max = arr[i];
            break;
        }
    }
    return max;
}