int func0(int n) {
    int i, j, ctr = 0;
    for (i = 0; i < n; i++) {
        int isPrime = 1;
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            ctr++;
        }
    }
    return ctr;
}