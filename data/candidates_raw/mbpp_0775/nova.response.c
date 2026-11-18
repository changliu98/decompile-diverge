int func0(int *arr, int n) {
    int i = 0;
    char flag = 1;
    while (i < n) {
        if (arr[i] % 2!= i % 2) {
            flag = 0;
            break;
        }
        i++;
    }
    return flag & 1;
}