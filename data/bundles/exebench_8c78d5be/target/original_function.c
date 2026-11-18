static int enddata(char *buff, int p)
{
 int pageaddr, offset;

 offset = p & 63;
 pageaddr = p-offset;

 if (offset == 0)
  return 0;

 buff[pageaddr + 1] = offset - 1;
 p = pageaddr + 64;

 return p;
}