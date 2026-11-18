static unsigned char crc_8(unsigned char *data, unsigned long len)
{
    unsigned long i;
    unsigned char crc = 0;
    if (data != ((void *)0))
    {
        for (i = 0; i < len; i++)
        {
            crc = sht75_crc_table[(crc ^ data[i]) & 0xff];
        }
    }
    return (crc);
}