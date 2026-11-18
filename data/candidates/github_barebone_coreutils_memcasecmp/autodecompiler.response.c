int memcasecmp(const void *b1, const void *b2, size_t len)
{
    const unsigned char *c1 = b1, *c2 = b2;
    unsigned char ch;
    int d = 0;
    size_t i;

    for (i = 0; i < len; i++) {
 d = ((int)(toupper(ch = *c1++))) - ((int)(toupper(ch = *c2++)));
 if (d || !ch)
     break;
    }

    return d;
}