int parity(int n) {
    int p = 0;
    while (n != 0) {
        n &= (n-1);
        p++;
    }
    return (p % 2 == 1);
}