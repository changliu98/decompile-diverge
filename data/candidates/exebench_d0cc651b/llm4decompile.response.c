void increment(unsigned int *n)
{
    unsigned int c, w;

    w = 1;
    c = *n;
    while (c & w) {
        c ^= w;
        w <<= 1;
    }
    *n = c ^ w;
}