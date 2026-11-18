BITCODE_TU __cdecl bit_utf8_to_TU(char *str, const unsigned int cquoted)
{
  unsigned __int8 *v2; // rax
  unsigned __int8 *v3; // rax
  size_t v4; // rcx
  size_t v5; // rcx
  size_t v6; // rcx
  size_t v7; // rcx
  size_t v8; // rcx
  bool v10; // [rsp+Eh] [rbp-32h]
  unsigned __int8 c; // [rsp+Fh] [rbp-31h]
  size_t len; // [rsp+10h] [rbp-30h]
  size_t i; // [rsp+18h] [rbp-28h]
  BITCODE_RS *wstr; // [rsp+20h] [rbp-20h]
  char *stra; // [rsp+30h] [rbp-10h]

  stra = str;
  i = 0LL;
  len = strlen(str);
  if ( len > 0xFFFE )
  {
    loglevel = 1;
    len = 65534LL;
  }
  wstr = (BITCODE_RS *)calloc(2uLL, len + 1);
  if ( wstr )
  {
    while ( 1 )
    {
      v10 = 0;
      if ( len )
      {
        v2 = (unsigned __int8 *)stra++;
        c = *v2;
        v10 = *v2 != 0;
      }
      if ( !v10 )
        break;
      --len;
      if ( c >= 0x80u )
      {
        if ( (c & 0xE0) == 192 )
        {
          if ( len )
          {
            v7 = i++;
            wstr[v7] = stra[1] & 0x3F | ((c & 0x1F) << 6);
          }
          --len;
          ++stra;
        }
        else if ( (c & 0xF0) == 224 )
        {
          if ( len >= 2 )
          {
            v8 = i++;
            wstr[v8] = stra[2] & 0x3F | ((stra[1] & 0x3F) << 6) | ((c & 0xF) << 12);
          }
          stra += 2;
          len -= 2LL;
        }
      }
      else if ( cquoted && c == 92 && len > 1 && (*stra == 34 || *stra == 92 || *stra == 114 || *stra == 110) )
      {
        v3 = (unsigned __int8 *)stra++;
        c = *v3;
        if ( *v3 == 114 )
        {
          v4 = i++;
          wstr[v4] = 13;
        }
        else
        {
          v5 = i++;
          if ( c == 110 )
            wstr[v5] = 10;
          else
            wstr[v5] = c;
        }
      }
      else
      {
        v6 = i++;
        wstr[v6] = c;
      }
    }
    return wstr;
  }
  else
  {
    loglevel = 1;
    return 0LL;
  }
}