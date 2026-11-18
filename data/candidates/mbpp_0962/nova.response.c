int func0(int n, int x) {
    int a = x / 2, b = x / 2;
    if (x % 2!= 0)
        b++;
    return a * (n - 1) - b * (n + 1) / 2;
}