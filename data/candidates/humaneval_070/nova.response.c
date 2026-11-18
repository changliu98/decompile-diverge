void func0(int *arr, int arr_len, int *sorted_arr) {
    int i, j, k;
    for (i = 0; i < arr_len - 1; i++) {
        for (j = i + 1; j < arr_len; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    for (k = 0, i = 0, j = arr_len - 1; i <= j; i++, j--) {
        if (i == j) {
            sorted_arr[k++] = arr[i];
        } else {
            sorted_arr[k++] = arr[i];
            sorted_arr[k++] = arr[j];
        }
    }
}