void __cdecl dwordstore(char *p, const int d)
{
  *p = d;
  *(_WORD *)(p + 1) = (unsigned int)d >> 8;
  p[3] = HIBYTE(d);
}