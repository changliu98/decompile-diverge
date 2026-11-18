long long func0(int n) {
    int k = n / 2;
    long long x = pow(2, k);
    long long y = x / (k + 1);
    return y;
}