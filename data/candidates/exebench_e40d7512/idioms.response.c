char *scnline(int i, char *str, int c)
{
  int j = 8;
  while ( --j )
    str++[(i <<= 1) & 0x80 ? c : ' '] = 0;
  return str;
}