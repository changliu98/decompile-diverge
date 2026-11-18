int func0(int n) {
    int i, j;
    char flag;
    for (i = 2; i < n; i++) {
        j = n / i;
        if (j <= i) {
            if (n % i == 0) {
                flag = 0;
                break;
            } else {
                flag = 1;
            }
        }
    }
    if (flag % 2 == 0)
        return 0;
    else
        return 1;
}