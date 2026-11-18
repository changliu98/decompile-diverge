void get_rgb15(int p, int *r, int *g, int *b)
{
 *b = p & 0x1f;
 if (*b & 0x10) *b |= 0xf0;
 *b <<= 1;
 *g = (p & 0x3e0) >> 5;
 if (*g & 0x10) *g |= 0xf0;
 *r = (p & 0x7c00) >> 10;
 if (*r & 0x10) *r |= 0xf0;
}