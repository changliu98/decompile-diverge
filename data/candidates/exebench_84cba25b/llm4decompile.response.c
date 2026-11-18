char *base91(char *q, uint16_t x)
{
    *q++ = '!' + x / 91;
    *q++ = '!' + x % 91;
    return q;
}