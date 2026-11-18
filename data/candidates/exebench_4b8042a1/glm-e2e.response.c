int next_arr_seq(int *arr, int size, int max_val) {
    for (int i = 0; i < size; i++) {
        arr[i]++;
        if (arr[i] <= max_val) {
            return 1;
        }
        arr[i] = 0;
    }
    return 0;
}