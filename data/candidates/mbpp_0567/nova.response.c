int func0(int *arr, int n) {
    int i = 0;
    char flag = 1;
    while (i < n - 1) {
        if (arr[i] > arr[i + 1]) {
            flag = 0;
            break;
        }
        i++;
    }
    return flag & 1;
}