int func0(int *a, int n) {
    int i = 0;
    char flag = 1;
    while (flag) {
        if (i < n - 1) {
            if (a[i] >= a[i + 1]) {
                flag = 0;
            } else {
                i++;
            }
        } else {
            flag = 0;
        }
    }
    return i % 2;
}