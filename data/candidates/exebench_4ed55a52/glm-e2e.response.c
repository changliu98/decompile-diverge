void shift_array(char *arr) {
    int i = 0;
    while (arr[i] != 0) {
        arr[i] += 5;
        i++;
    }
}