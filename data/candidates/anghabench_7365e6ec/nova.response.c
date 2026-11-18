int llc_shdlc_w_used(int a, int b) {
    int c;
    if (b <= a)
        c = a - b;
    else
        c = a + 8 - b;
    return c;
}