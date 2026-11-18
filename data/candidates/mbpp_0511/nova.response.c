int func0(int n) {
    int sum = 0;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            sum += i;
            n /= i;
        }
    }
    sum += n;
    return sum;
}