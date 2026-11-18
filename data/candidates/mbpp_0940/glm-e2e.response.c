void func0(int *arr, int n) {
    int temp;
    int i;

    heapify(arr, n);

    for (i = n - 1; i > 0; i--) {
        temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        
        shift_down(arr, 0, i);
    }
}