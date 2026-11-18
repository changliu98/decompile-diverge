int swizzle(unsigned int a, unsigned int b) {
    int result = 0;
    while (b != 0) {
        result = (result << 1) | (a & 1);
        a >>= 1;
        b >>= 1;
    }
    return result;
}