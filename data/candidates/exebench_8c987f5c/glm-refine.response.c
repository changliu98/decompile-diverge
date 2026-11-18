const char *__cdecl minimum_size_type(int lwr, int upr, int *pnByte)
{
  const char *zType;
  int nByte;

  if (lwr < 0)
  {
    // Signed types
    if (lwr < -127 || upr > 127)
    {
      // Does not fit in a signed char; check if it fits in a short
      if (lwr >= -32767 && upr < 0x7FFF)
      {
        zType = "short";
        nByte = 2;
      }
      else
      {
        // Falls back to default int
        zType = "int";
        nByte = 4;
      }
    }
    else
    {
      zType = "signed char";
      nByte = 1;
    }
  }
  else
  {
    // Unsigned types
    if (upr > 255)
    {
      if (upr >= 0xFFFF)
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
  }

  if (pnByte)
    *pnByte = nByte;

  return zType;
}