static int enddata(unsigned char *s, uint64_t v)
{
    int n, t;

    n = v & 0x3f;
    t = v - n;
    if (t == 0) {
        if (n == 0) {
            *s++ = 'A';
        } else {
            *s++ = 'B';
        }
        v = n;
    } else {
        v = n + 1;
    }
    for (n = 0; v > 0; n++) {
        v >>= 6;
    }
    *s++ = (unsigned char)(n + 'a');
    return n;
}