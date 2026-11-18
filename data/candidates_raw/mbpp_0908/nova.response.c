int func0(int *arr, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        if (arr[i] == i) {
            j = i;
            break;
        }
    }
    if (i == size) {
        j = -1;
    }
    return j;
}