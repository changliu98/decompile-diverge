int func0(int *arr, int n) {
    int i, j, k;
    i = 0;
    j = 0;
    while (j < n) {
        if (arr[j] % 2 == 0) {
            i++;
        } else {
            j++;
        }
    }
    if (i % 2 == 0) {
        k = 1;
    } else {
        k = 2;
    }
    return k;
}