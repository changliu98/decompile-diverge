int func0(long a, long b) {
    long n = a + b;
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}