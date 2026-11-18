int func0(int n) {
    int i = 2;
    while (1) {
        if (i * i > n) {
            return n;
        }
        while (n % i == 0) {
            n /= i;
        }
        if (n % 2 == 0) {
            continue;
        }
        i++;
    }
}