int func0(int n) {
    int i, j = 0;
    for (i = 1;; i++) {
        if (i <= n) {
            if (n % i == 0)
                j++;
        } else
            break;
    }
    return j;
}