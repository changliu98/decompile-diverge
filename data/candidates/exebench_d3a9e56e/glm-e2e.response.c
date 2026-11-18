void reverseInt(int *arr) {
    for (int i = 0; i < 5; i++) {
        int temp = arr[i];
        arr[i] = arr[10 - i - 1];
        arr[10 - i - 1] = temp;
    }
}