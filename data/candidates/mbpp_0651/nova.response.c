bool func0(int *a, int n, int *b, int m) {
    int i, j;
    bool flag;
    for (i = 0; i < m; i++) {
        flag = false;
        for (j = 0; j < n; j++) {
            if (b[i] == a[j]) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            return false;
        }
    }
    return true;
}