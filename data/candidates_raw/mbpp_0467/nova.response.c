int func0(int n) {
    int rev = 0, base = 1;
    while (n) {
        int r = n % 8;
        rev += r * base;
        base *= 10;
        n /= 8;
    }
    return rev;
}