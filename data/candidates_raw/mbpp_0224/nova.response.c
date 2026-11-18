int func0(int n) {
    int sum = 0;
    while (n) {
        sum += n & 1;
        n >>= 1;
    }
    return sum;
}