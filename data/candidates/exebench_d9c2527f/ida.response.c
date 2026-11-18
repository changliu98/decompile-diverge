const char *__cdecl get_word(const char *str, int *len)
{
  bool v3; // [rsp+1h] [rbp-17h]
  char v4; // [rsp+2h] [rbp-16h]
  char v5; // [rsp+3h] [rbp-15h]
  int i; // [rsp+4h] [rbp-14h]
  const char *stra; // [rsp+10h] [rbp-8h]

  stra = str;
  i = 0;
  if ( str )
  {
    while ( *stra == 45 )
      ++stra;
    if ( *stra >= 97 && *stra <= 122 )
    {
      while ( 1 )
      {
        v5 = 0;
        if ( i < 64 )
        {
          if ( stra[i] < 48 || (v4 = 1, stra[i] > 57) )
          {
            if ( stra[i] < 97 || (v4 = 1, stra[i] > 122) )
            {
              v3 = 1;
              if ( stra[i] != 45 )
                v3 = stra[i] == 95;
              v4 = v3;
            }
          }
          v5 = v4;
        }
        if ( (v5 & 1) == 0 )
          break;
        ++i;
      }
    }
  }
  *len = i;
  return stra;
}