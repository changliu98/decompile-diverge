int next_arr_seq(int *arr, int size, int max) {
    int i = 0;
    int ret;
    while (i < size) {
        arr[i]++;
        if (arr[i] <= max) {
            ret = 1;
            break;
        } else {
            arr[i] = 0;
            i++;
        }
    }
    if (i == size)
        ret = 0;
    return ret;
}