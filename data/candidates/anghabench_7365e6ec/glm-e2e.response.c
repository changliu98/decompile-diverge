int llc_shdlc_w_used(int a, int b) {
    int c;
    if (b > a) {
        c = 8 - b + a;
    } else {
        c = a - b;
    }
    return c;
}