int func0(int x) {
    int k, y;
    if (x == 0)
        y = 1;
    else if ((x & (x + 1)) == 0)
        y = x;
    else {
        k = log2(x & (~(x >> 1)));
        y = (1 << k) | x;
    }
    return y;
}