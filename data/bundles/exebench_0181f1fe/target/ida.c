int __cdecl ellipsis(char *str, int len)
{
  char *v2; // rax
  char *v3; // rax
  bool v5; // [rsp+0h] [rbp-2Ah]
  bool v6; // [rsp+1h] [rbp-29h]
  char *ptr; // [rsp+2h] [rbp-28h]
  char *ptra; // [rsp+2h] [rbp-28h]
  char *ptrb; // [rsp+2h] [rbp-28h]
  int inGBK; // [rsp+Eh] [rbp-1Ch]
  int i; // [rsp+12h] [rbp-18h]
  int ia; // [rsp+12h] [rbp-18h]

  inGBK = 0;
  ptr = str;
  if ( len < 0 || !str )
    return 0;
  if ( len >= 3 )
  {
    for ( i = len - 3; ; --i )
    {
      v6 = 0;
      if ( *ptr )
        v6 = i != 0;
      if ( !v6 )
        break;
      if ( inGBK )
        inGBK = 0;
      else
        inGBK = *ptr < 0;
      ++ptr;
    }
    ia = 3;
    do
    {
      v2 = ptr++;
      v5 = 0;
      if ( *v2 )
        v5 = --ia != 0;
    }
    while ( v5 );
    if ( *ptr )
    {
      if ( !ia )
      {
        str[len] = 0;
        *(ptr - 1) = 46;
        ptra = ptr - 2;
        *ptra = 46;
        if ( !inGBK )
        {
          v3 = ptra;
          ptrb = ptra - 1;
          if ( (*(v3 - 1) & 0x80) != 0 )
            *ptrb = 46;
        }
      }
    }
    return 1;
  }
  else
  {
    str[len] = 0;
    return 1;
  }
}