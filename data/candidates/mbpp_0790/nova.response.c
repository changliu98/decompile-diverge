int func0(int *arr, int n) {
    int i = 0;
    char flag;
    while (i < n) {
        if (arr[i] % 2!= i % 2) {
            flag = 0;
            break;
        } else
            flag = 1;
        i++;
    }
    return flag & 1;
}