int func0(int n) {
    int primes[3000] = {0};
    int ugly[3000] = {0};
    int cnt = 0;
    int i, j, k, min, pos;

    for (i = 2; ; i++) {
        if (cnt >= 3000) break;
        if (primes[i]) continue;
        primes[i] = 1;
        k = i * 2;
        while (k < 3000) {
            primes[k]--;
            if (primes[k] == -3) ugly[cnt++] = k;
            k += i;
        }
    }

    for (i = 0; i < cnt - 1; i++)
        for (j = 0; j < cnt - i - 1; j++)
            if (ugly[j] > ugly[j + 1])
                { min = ugly[j]; ugly[j] = ugly[j + 1]; ugly[j + 1] = min; };
    return ugly[n - 1];
}