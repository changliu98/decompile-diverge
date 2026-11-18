int func0(int *arr, int size) {
    if (size < 2) {
        return -1;
    }

    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2 && arr[i] != min1) {
            min2 = arr[i];
        }
    }

    if (min2 == INT_MAX) {
        return -1;
    }

    return min2;
}