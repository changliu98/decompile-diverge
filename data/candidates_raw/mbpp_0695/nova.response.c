int func0(int *a, int *b, int n) {
    int i = 0;
    char flag = 1;
    while (i < n) {
        if (a[i] < b[i]) {
            flag = 0;
            break;
        }
        i++;
    }
    return flag & 1;
}