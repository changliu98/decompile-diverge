Fnv32_t fnv_32a_buf(void *buf, size_t len, Fnv32_t hval)
{
    unsigned char *bp = (unsigned char *)buf;
    unsigned char *be = bp + len;




    while (bp < be) {


 hval ^= (Fnv32_t)*bp++;




 hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);

    }


    return hval;
}