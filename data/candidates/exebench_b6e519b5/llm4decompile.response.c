int u_get(uint32_t *up, const char *s)
{
    if ((*(const unsigned char *) s < 0x80)) {
 *up = *(const unsigned char *) s;
 return 1;
    } else if ((*(const unsigned char *) s < 0xc0)) {
 return 0;
    } else if ((*(const unsigned char *) s < 0xe0)) {
 *up = ((*(const unsigned char *)(s) & 0x1f) << 6) | (*(const unsigned char *)(s + 1) & 0x3f);
 if (*up & 0xffffff80)
     return 2;
 return 0;
    } else if ((*(const unsigned char *) s < 0xf0)) {
 *up = (((*(const unsigned char *)(s) & 0x0f) << 12) | ((*(const unsigned char *)(s + 1) & 0x3f) << 6) | (*(const unsigned char *)(s + 2) & 0x3f));
 if (*up & 0xfffff800)
     return 3;
 return 0;
    } else if ((*(const unsigned char *) s < 0xf8)) {
 *up = ((((int)(*(const unsigned char *)(s) & 0x07)) << 18) | ((*(const unsigned char *)(s + 1) & 0x3f) << 12) | ((*(const unsigned char *)(s + 2) & 0x3f) << 6) | (*(const unsigned char *)(s + 3) & 0x3f));
 if (*up & 0xffff0000)
     return 4;
 return 0;
    } else if ((*(const unsigned char *) s < 0xfc)) {
 *up = (((((int)(*(const unsigned char *)(s) & 0x03)) << 24) | ((*(const unsigned char *)(s + 1) & 0x3f) << 18) | ((*(const unsigned char *)(s + 2) & 0x3f) << 12) | ((*(const unsigned char *)(s + 3) & 0x3f) << 6) | (*(const unsigned char *)(s + 4) & 0x3f));
 if (*up & 0xffe00000)
     return 5;
 return 0;
    } else if ((*(const unsigned char *) s < 0xfe)) {
 *up = ((((((int)(*(const unsigned char *)(s) & 0x01)) << 30) | ((*(const unsigned char *)(s + 1) & 0x3f) << 24) | ((*(const unsigned char *)(s + 2) & 0x3f) << 18) | ((*(const unsigned char *)(s + 3) & 0x3f) << 12) | ((*(const unsigned char *)(s + 4) & 0x3f) << 6) | (*(const unsigned char *)(s + 5) & 0x3f));
 if (*up & 0xfc000000)
     return 6;
 return 0;
    } else {
 return 0;
    }
}