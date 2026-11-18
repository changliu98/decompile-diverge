int func0(int n) {
    int i = 0;
    while (n) {
        n = n & (n - 1);
        i++;
    }
    return i % 2 == 0;
}