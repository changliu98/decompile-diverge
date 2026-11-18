int __cdecl utoa(char *str, unsigned int u, int spec)
{
  const char *hex;
  char hexupper[17];
  char hexlower[17];
  int base;
  char *p;
  char *end;
  char tmp[128];
  char v18;
  unsigned int ua;

  ua = u;
  end = &v18;
  p = &tmp[127];
  strcpy(hexlower, "0123456789abcdef");
  strcpy(hexupper, "0123456789ABCDEF");
  
  switch ( spec )
  {
    case 'X':
      base = 16;
      hex = hexupper;
      goto LABEL_7;
    case 'd':
    case 'i':
    case 'u':
      base = 10;
      goto LABEL_7;
    case 'o':
      base = 8;
      goto LABEL_7;
    case 'x':
      base = 16;
      hex = hexlower;
      do
      {
LABEL_7:
        switch ( base )
        {
          case 8:
            *p-- = (ua & 7) + 48;
            break;
          case 10:
            *p-- = ua % 10 + 48;
            break;
          case 16:
            *p-- = hex[ua & 0xF];
            break;
        }
        ua /= (unsigned int)base;
      }
      while ( ua );
      
      ++p;
      while ( p < end )
      {
        *str++ = *p++;
      }
      *str = 0;
      return (int)(str - (char*)u); // Note: Original code computes pointer diff using initial 'u' due to register reuse
    default:
      return -1;
  }
}