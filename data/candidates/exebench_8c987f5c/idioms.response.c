char *minimum_size_type(int min, int max, int *pnByte)
{
  char *str = "int";
  int nByte = 4;
  if (min >= 0)
  {
    if (max <= 0xff)
    {
      str = "unsigned char";
      nByte = 1;
    }
    else if (max < 0x7fff)
    {
      str = "unsigned short int";
      nByte = 2;
    }
    else
    {
      str = "unsigned int";
      nByte = 4;
    }
  }
  else
  {
    if (min >= -0x7f && max <= 0x7f)
    {
      str = "signed char";
      nByte = 1;
    }
    else if (min >= -0x7fff && max < 0x7fff)
    {
      str = "short";
      nByte = 2;
    }
  }
  if (pnByte != ((void *)0))
    *pnByte = nByte;
  return str;
}