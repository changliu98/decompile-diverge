void copy_le16(unsigned char *p, unsigned int v)
{
 p[0] = (unsigned char)((v >> 0) & 0xff);
 p[1] = (unsigned char)((v >> 8) & 0xff);
}