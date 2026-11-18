int func0(int n) {
    int i = 0, res = 0, m = n;
    while (m > 0) {
        if (i % 2 == 1)
            res |= 1 << i;
        i++;
        m >>= 1;
    }
    return res | n;
}