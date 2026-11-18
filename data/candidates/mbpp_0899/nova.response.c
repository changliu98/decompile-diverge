int func0(int *a, int n) {
    int i, j, k, l;
    char flag;
    for (i = 0, j = 1, k = 0;; i++) {
        if (i < n) {
            if (a[i] - a[i - 1] > 0 && j == 1) {
                flag = 0;
                break;
            } else if (a[i] - a[i - 1] < 0) {
                j = 1;
            }
        } else {
            flag = 1;
            break;
        }
    }
    return flag & 1;
}