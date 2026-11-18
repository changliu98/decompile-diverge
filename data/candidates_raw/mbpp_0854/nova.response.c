void func0(int *arr, int arr_len) {
    int i, j, k, temp;
    for (i = (arr_len / 2 - 1); i >= 0; i--) {
        for (j = (i * 2 + 1); j < arr_len; j = j * 2 + 1) {
            if (j + 1 < arr_len && arr[j] < arr[j + 1]) {
                j++;
            }
            if (arr[i] > arr[j]) {
                break;
            } else {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}