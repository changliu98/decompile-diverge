void int2str(int v, int digits, char *output)
{
    while (digits) {
        *output++ = '0' + (v / digits) % 10;
        digits /= 10;
    }
}