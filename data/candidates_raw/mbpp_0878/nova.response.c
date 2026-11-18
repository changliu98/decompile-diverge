int func0(int *a, int n, int *b, int m) {
    int i, j;
    bool flag;
    for (i = 0; i < n; i++) {
        flag = false;
        for (j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                flag = true;
                break;
            }
        }
        if (flag == false)
            return false;
    }
    return true;
}