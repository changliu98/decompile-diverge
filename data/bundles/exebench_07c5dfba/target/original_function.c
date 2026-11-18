void _itoa_dec(unsigned int val, char *buf)
{
    const static char dectab[] = "0123456789";
    unsigned int i;

    for (i = 0; i < 10; i++)
    {
        if ((val != 0) || (i == 0))
            buf[9-i] = dectab[val % 10];
        else
            buf[9-i] = 0x20;
        val /= 10;
    }
}