int __cdecl ISORegexp__get_cclass(char *pattern, int ppos, int *len, int *from, int *to, int *reverse)
{
  bool v7; // [rsp+1h] [rbp-49h]
  int v8; // [rsp+Eh] [rbp-3Ch]
  int pposa; // [rsp+36h] [rbp-14h]
  int pposb; // [rsp+36h] [rbp-14h]
  int v11; // [rsp+46h] [rbp-4h]

  pposa = ppos;
  if ( pattern[ppos] == 94 )
  {
    pposa = ppos + 1;
    *reverse = 1;
  }
  else
  {
    *reverse = 0;
  }
  v8 = pattern[pposa];
  switch ( v8 )
  {
    case ' ':
      *len = 1;
      return 3;
    case '%':
      pposb = pposa + 1;
      *len = 2;
      switch ( pattern[pposb] )
      {
        case 'C':
          v11 = 4;
          break;
        case 'P':
          v11 = 7;
          break;
        case 'c':
          v11 = 1;
          break;
        case 'd':
          v11 = 2;
          break;
        case 'i':
          v11 = 5;
          break;
        case 'p':
          v11 = 6;
          break;
        case 't':
          v11 = 9;
          break;
        default:
          *from = pposb;
          *to = pposb;
          v11 = 8;
          break;
      }
      break;
    case '[':
      *from = pposa + 2;
      while ( 1 )
      {
        v7 = 0;
        if ( pattern[pposa] )
          v7 = pattern[pposa] != 93;
        if ( !v7 )
          break;
        ++pposa;
      }
      *to = pposa - 1;
      *len = pposa - *from + 1;
      return 8;
    default:
      *len = 1;
      *from = pposa;
      *to = pposa;
      return 8;
  }
  return v11;
}