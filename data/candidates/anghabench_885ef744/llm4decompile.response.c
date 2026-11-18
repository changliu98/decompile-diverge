void ui2a(unsigned int num, int base, int uc, char *bf)
{
    int dgt, div, n;

    for (div = 1; div <= num / base; div *= base);

    for (n = 0; div; div /= base) {
        dgt = num / div;
        num %= div;
        if (n || dgt > 0 || !div) {
            *bf++ = (dgt > 9) ? (uc ? 'A' : 'a') + dgt - 10 : '0' + dgt;
            n++;
        }
    }
    *bf = '\0';
}