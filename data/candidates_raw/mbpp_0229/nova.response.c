int func0(int *a, int *b, int n) {
    int i;
    bool flag;
    for (i = 0; i < n; i++) {
        if (a[i]!= b[i]) {
            flag = false;
            break;
        } else
            flag = true;
    }
    return flag;
}