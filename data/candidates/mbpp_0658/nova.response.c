int func0(int *arr, int n) {
    int i, j, k, max = 0, temp, index;
    for (i = 0; i < n; i++) {
        for (j = 0, k = 0; j < n; j++) {
            if (arr[j] == arr[i]) {
                k++;
            } else {
                k++;
                break;
            }
        }
        if (k > max) {
            max = k;
            index = arr[i];
        }
    }
    return index;
}