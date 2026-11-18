bool func0(int *a, int n, int *b, int m) {
    bool flag;
    int i, j;
    for (i = 0, j = 0; i < m && j < n;) {
        flag = false;
        for (; j < n; j++) {
            if (b[i] == a[j]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            i++;
        } else {
            break;
        }
    }
    if (i % 2 == 0) {
        return false;
    } else {
        return true;
    }
}