int func0(int n) {
    int i, j, k, flag;
    if (n < 3)
        flag = 0;
    else {
        k = 0;
        for (i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                n /= i;
                k++;
            }
        }
        if (n > 1)
            k++;
        if (k == 3)
            flag = 1;
        else
            flag = 0;
    }
    return flag;
}