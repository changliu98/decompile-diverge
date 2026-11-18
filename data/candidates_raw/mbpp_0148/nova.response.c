int func0(int n) {
    int k = f(n);
    int l = f(n - k);
    return l + f(n - k);
}