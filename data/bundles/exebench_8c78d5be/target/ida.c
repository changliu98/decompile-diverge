int __cdecl enddata(char *buff, int p)
{
  int offset; // [rsp+0h] [rbp-1Ch]
  int pageaddr; // [rsp+4h] [rbp-18h]

  offset = p & 0x3F;
  pageaddr = p - offset;
  if ( (p & 0x3F) == 0 )
    return 0;
  buff[pageaddr + 1] = offset - 1;
  return pageaddr + 64;
}