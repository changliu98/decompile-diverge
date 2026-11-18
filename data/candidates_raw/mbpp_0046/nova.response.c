int func0(int *arr, int n) {
    int i, j;
    char flag;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                flag = 0;
                break;
            } else
                flag = 1;
        }
    }
    return flag & 1;
}