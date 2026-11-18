int func0(int n) {
    int sum = 1;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}