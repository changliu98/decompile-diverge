int func0(int n, int m) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result = (result * 2) % m;
    }
    return result;
}