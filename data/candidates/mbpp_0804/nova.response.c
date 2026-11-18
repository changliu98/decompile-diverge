int func0(int *arr, int size) {
    int i;
    bool odd_even;

    for (i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            odd_even = true;
        } else {
            odd_even = false;
            break;
        }
    }
    return odd_even;
}