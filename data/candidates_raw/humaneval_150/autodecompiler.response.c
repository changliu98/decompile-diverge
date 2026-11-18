int is_prime(int n, int p_if_true, int p_if_false) {
    int i;
    int flag = 1;
    if (n < 2)
        flag = 0;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0)
            flag = 0;
    }
    int ret;
    if (flag)
        ret = p_if_true;
    else
        ret = p_if_false;
    return ret;
}