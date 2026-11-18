int func0(int n) {
    int sum = 0, sumsq = 0;
    for (int i = 1;; i++) {
        if (i <= n) {
            sum += i * i;
            sumsq += i;
        } else {
            sumsq *= sumsq;
            break;
        }
    }
    return sumsq - sum;
}