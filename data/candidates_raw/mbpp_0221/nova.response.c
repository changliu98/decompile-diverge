int func0(int *arr, int size) {
    int i = 0;
    int result;
    while (i < size) {
        if (arr[i] % 2 == 0) {
            result = arr[i];
            break;
        } else {
            i++;
        }
    }
    if (i >= size) {
        result = -1;
    }
    return result;
}