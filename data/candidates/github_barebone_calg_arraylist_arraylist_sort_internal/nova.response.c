void arraylist_sort_internal(char **arr, unsigned int arr_len, char *str) {
    if (arr_len <= 1)
        return;

    char *pivot = arr[arr_len - 1];
    unsigned int i = 0, j = 0;
    for (; j < arr_len - 1; ++j) {
        if (strcmp(arr[j], pivot) < 1) {
            char *tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
            ++i;
        }
    }
    unsigned int swap_index = arr_len - i - 1;
    arr[arr_len - 1] = arr[i];
    arr[i] = pivot;
    arraylist_sort_internal(arr, i, str);
    arraylist_sort_internal(arr + i + 1, arr_len - i - 1, str);
}