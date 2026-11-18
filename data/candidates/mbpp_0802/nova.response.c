int func0(int *arr, int n) {
    int i = 1, j;
    while (1) {
        if (i >= n) {
            j = 0;
            break;
        }
        if (arr[i] < arr[i - 1]) {
            j = i;
            break;
        }
        i++;
    }
    return j;
}