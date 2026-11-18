char *func0(unsigned int parity)
{
    char *ret;
    unsigned int tmp;

    tmp = parity ^ (parity >> 1);
    tmp ^= tmp >> 2;
    tmp ^= tmp >> 4;
    tmp ^= tmp >> 8;
    tmp ^= tmp >> 16;

    if (tmp & 1) {
        ret = "Odd Parity";
    } else {
        ret = "Even Parity";
    }

    return ret;
}