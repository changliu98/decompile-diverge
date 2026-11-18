int func0(int n) {
    int i, j, flag = 0;
    for (i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}