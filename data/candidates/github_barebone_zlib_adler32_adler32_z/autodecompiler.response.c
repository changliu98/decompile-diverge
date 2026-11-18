unsigned long adler32_z(unsigned long adler, unsigned char *buf, unsigned long len)
{
    unsigned long sum2;
    unsigned n;


    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;


    if (len == 1) {
        adler += buf[0];
        if (adler >= 65521UL)
            adler -= 65521UL;
        sum2 += adler;
        if (sum2 >= 65521UL)
            sum2 -= 65521UL;
        return adler | (sum2 << 16);
    }


    if (buf == (unsigned char *)0)
        return 1L;


    if (len < 16) {
        while (len--) {
            adler += *buf++;
            sum2 += adler;
        }
        if (adler >= 65521UL)
            adler -= 65521UL;
        sum2 %= 65521UL;
        return adler | (sum2 << 16);
    }


    while (len >= 5552) {
        n = 5552 / 2;
        do {
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
        } while (--n);
        adler %= 65521UL;
        sum2 %= 65521UL;
        len -= 5552;
    }


    if (len) {
        while (len >= 16) {
            len -= 16;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
            adler += *buf++;
            sum2 += adler;
        }
        while (len--) {
            adler += *buf++;
            sum2 += adler;
        }
        adler %= 65521UL;
        sum2 %= 65521UL;
    }


    return adler | (sum2 << 16);
}