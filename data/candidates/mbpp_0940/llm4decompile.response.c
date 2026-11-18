void func0(int *arr, int length) {
    heapify(arr, length);
    int end = length - 1;
    while (end > 0) {
        int tmp = arr[end];
        arr[end] = arr[0];
        arr[0] = tmp;
        shift_down(arr, 0, end - 1);
        end--;
    }
}