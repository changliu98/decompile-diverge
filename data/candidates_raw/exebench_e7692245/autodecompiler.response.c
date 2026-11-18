static void put_le32(unsigned char *p, int v)
{
 p[0] = v & 0xff;
 p[1] = (v >> 8) & 0xff;
 p[2] = (v >> 16) & 0xff;
 p[3] = (v >> 24) & 0xff;
}