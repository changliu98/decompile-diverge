int func0(int n) {
    int i, j = -1;
    while (1) {
        if (n % 2 == 0) {
            j = 2;
            n = n / 2;
        } else {
            for (i = 3; i <= sqrt(n); i = i + 2) {
                if (n % i == 0) {
                    j = i;
                    n = n / i;
                    break;
                }
            }
            if (n > 2) {
                j = n;
                break;
            }
        }
    }
    return j;
}