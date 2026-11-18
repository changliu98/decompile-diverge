static int
u_get(unsigned int *uc, unsigned char *utf)
{
    unsigned char *p;
    int len;

    p = utf;

    if (*p < 0x80) {
 *uc = *p;
 len = 1;
    } else if (*p < 0xc0) {

 len = 0;
    } else if (*p < 0xe0) {
 *uc = ((*p & 0x1f) << 6) | (*(p + 1) & 0x3f);
 len = (*uc & 0xff80) ? 2 : 0;
    } else if (*p < 0xf0) {
 *uc = ((*p & 0x0f) << 12) | ((*(p + 1) & 0x3f) << 6) | (*(p + 2) & 0x3f);
 len = (*uc & 0xfffff800) ? 3 : 0;
    } else if (*p < 0xf8) {
 *uc = ((*p & 0x07) << 18) | ((*(p + 1) & 0x3f) << 12) |
       ((*(p + 2) & 0x3f) << 6) | (*(p + 3) & 0x3f);
 len = (*uc & 0x1fffff00) ? 4 : 0;
    } else if (*p < 0xfc) {
 *uc = ((*p & 0x03) << 24) | ((*(p + 1) & 0x3f) << 18) |
       ((*(p + 2) & 0x3f) << 12) | ((*(p + 3) & 0x3f) << 6) | (*(p + 4) & 0x3f);
 len = (*uc & 0xffe00000) ? 5 : 0;
    } else if (*p < 0xfe) {
 *uc = ((*p & 0x01) << 30) | ((*(p + 1) & 0x3f) << 24) |
       ((*(p + 2) & 0x3f) << 18) | ((*(p + 3) & 0x3f) << 12) |
       ((*(p + 4) & 0x3f) << 6) | (*(p + 5) & 0x3f);
 len = (*uc & 0xfc000000) ? 6 : 0;
    } else {

 len = 0;
    }

    return len;
}