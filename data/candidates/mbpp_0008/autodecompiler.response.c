void func0(int arr[], int result[], int size) {
    int i = 0;
    while (1) {
        if (i >= size) break;
        result[i] = arr[i] * arr[i];
        i++;
    }
}