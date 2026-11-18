const char *__cdecl minimum_size_type(int lwr, int upr, int *pnByte)
{
  int nByte; // [rsp+0h] [rbp-1Ch]
  char *zType; // [rsp+4h] [rbp-18h]

  zType = "int";
  nByte = 4;
  if ( lwr < 0 )
  {
    if ( lwr < -127 || upr > 127 )
    {
      if ( lwr >= -32767 && upr < 0x7FFF )
      {
        zType = "short";
        nByte = 2;
      }
    }
    else
    {
      zType = "signed char";
      nByte = 1;
    }
  }
  else if ( upr > 255 )
  {
    if ( upr >= 0xFFFF )
    {
      zType = "unsigned int";
      nByte = 4;
    }
    else
    {
      zType = "unsigned short int";
      nByte = 2;
    }
  }
  else
  {
    zType = "unsigned char";
    nByte = 1;
  }
  if ( pnByte )
    *pnByte = nByte;
  return zType;
}