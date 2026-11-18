int func0(int *arr, int n) {
    int i;
    char flag;
    if (n == 0)
        flag = 1;
    else {
        flag = 0;
        for (i = 1; i < n; i++) {
            if (arr[i] < arr[i - 1]) {
                flag = 0;
                break;
            }
            if (i >= 3) {
                if (arr[i] == arr[i - 1] && arr[i] == arr[i - 2])
                    flag = 0;
            }
        }
    }
    return flag & 1;
}