Fnv32_t fnv_32_buf(void *buf, size_t len, Fnv32_t hval)
{
    unsigned char *bp = (unsigned char *)buf;
    unsigned char *be = bp + len;




    while (bp < be) {


        hval ^= (Fnv32_t)*bp++;




        hval += (hval << 12);
        hval ^= (hval >> 22);




        hval += (hval << 4);
        hval ^= (hval >> 9);




        hval += (hval << 10);
        hval ^= (hval >> 2);
    }



    return hval;
}