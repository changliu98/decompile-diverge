int func0(int *arr, size_t size) {
    int i = 0;
    int min;
    while (i < size) {
        if (arr[i] < 0) {
            min = arr[i];
            break;
        }
        i++;
    }
    return min;
}