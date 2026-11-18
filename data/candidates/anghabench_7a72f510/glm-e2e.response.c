int gf_poly_mul2(int x) {
    int a = x & 0x7f7f7f7f;
    a = a << 1;
    int b = x & 0x80808080;
    b = b >> 7;
    b = b * 0x1b;
    return a ^ b;
}