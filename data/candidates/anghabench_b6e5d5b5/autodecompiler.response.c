static void packInt32(unsigned char *p, unsigned int v)
{
 p[0] = (unsigned char)(v & 0xff);
 p[1] = (unsigned char)((v >> 8) & 0xff);
 p[2] = (unsigned char)((v >> 16) & 0xff);
 p[3] = (unsigned char)((v >> 24) & 0xff);
}