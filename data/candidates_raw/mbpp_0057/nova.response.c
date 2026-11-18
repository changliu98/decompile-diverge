int func0(int *arr, int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    int sum = arr[0];
    for (int i = 1; i < size; i++) {
        sum = sum * 10 + arr[i];
    }
    return sum;
}