

void _itoa_hex(unsigned int val, char *buf)
{
    const static char hexatab[] = "0123456789ABCD";
    unsigned int i;

    for (i = 0; i < 8; i++)
    {
        buf[7-i] = hexatab[val % 16];
        val /= 16;
    }
}
