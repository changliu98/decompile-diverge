void putoct(char *buf, unsigned short val)
{
    char *p = buf + 7;
    *p-- = 0;
    *p-- = ' ';
    *p-- = (val & 07) + '0';
    while (p != buf) {
        val >>= 3;
        *p-- = val ? (val & 07) + '0' : ' ';
    }
}