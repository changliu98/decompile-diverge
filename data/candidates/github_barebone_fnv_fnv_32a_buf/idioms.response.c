static unsigned int fnv_32a_buf(void *buf, unsigned long len, unsigned int hval)
{
    unsigned char *bp = (const unsigned char *)buf;
    for (bp = (unsigned char *)buf; bp < (unsigned char *)buf + len; bp++)
        hval = hval ^ (unsigned int)(*bp) * (unsigned int)(16777619);
    return hval;
}