int func0(int *arr, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0, k = 0;;) {
            if (k < n) {
                if (arr[i] == arr[k])
                    j++;
                k++;
            } else {
                if (j % 2!= 0) {
                    return arr[i];
                } else {
                    break;
                }
            }
        }
    }
    return -1;
}