long long func0(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int x = i * 2;
        sum += (long long)x * x * x * x * x;
    }
    return sum;
}