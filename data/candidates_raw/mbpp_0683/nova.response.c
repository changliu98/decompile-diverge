int func0(int n) {
    int i, j;
    char flag;
    for (i = 1; i * i <= n; i++) {
        for (j = 1; j * j <= n; j++) {
            if (i * i + j * j == n) {
                flag = 1;
                break;
            } else
                flag = 0;
        }
    }
    return flag % 2;
}