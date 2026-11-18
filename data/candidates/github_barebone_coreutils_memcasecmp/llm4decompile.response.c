int memcasecmp(const void *l, const void *r, size_t n)
{
    const unsigned char *ll = (const unsigned char *)l;
    const unsigned char *rr = (const unsigned char *)r;
    size_t i;
    for (i = 0; i < n; i++) {
 int diff = toupper(ll[i]) - toupper(rr[i]);
 if (diff)
     return diff;
    }
    return 0;
}