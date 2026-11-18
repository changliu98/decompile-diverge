int func0(int x, int y) {
    int z = x ^ y;
    int d = 0;
    while (z > 0) {
        d += z & 1;
        z >>= 1;
    }
    return d;
}