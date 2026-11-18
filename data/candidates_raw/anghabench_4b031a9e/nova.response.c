int func0(long x) {
    int r;
    if ((x & 0x14) == 0) {
        r = 1;
    } else if ((x & 0x14) == 0x4) {
        r = ((x & 0x2) == 0);
    } else if ((x & 0x14) == 0x10) {
        r = ((x & 0x8) == 0);
    } else {
        r = (x == 0x14);
    }
    return r;
}