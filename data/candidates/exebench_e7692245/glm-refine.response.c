void __cdecl dwordstore(char *p, int d)
{
  *(unsigned char *)p       = (unsigned char)(d);
  *(unsigned short *)(p + 1) = (unsigned short)(d >> 8);
  *(unsigned char *)(p + 3) = (unsigned char)(d >> 24);
}