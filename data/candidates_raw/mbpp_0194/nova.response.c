int func0(int n) {
    int m = n;
    int sum = 0;
    int i = 1;
    while (m) {
        int r = m % 10;
        m = m / 10;
        sum = sum + r * i;
        i = i * 8;
    }
    return sum;
}