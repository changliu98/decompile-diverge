int func0(int n) {
    int c = 0;
    while (n) {
        n = n & (n - 1);
        c++;
    }
    return c % 2 == 1;
}