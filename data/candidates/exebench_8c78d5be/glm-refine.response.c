int __cdecl enddata(char *buff, int p)
{
  int offset = p & 0x3F;

  if (offset == 0)
    return 0;

  int pageaddr = p - offset;
  buff[pageaddr + 1] = offset - 1;
  
  return pageaddr + 64;
}