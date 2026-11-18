void __cdecl unescape(char *s, char *t)
{
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  j = 0;
  for ( i = 0; t[i]; ++i )
  {
    if ( t[i] == 92 )
    {
      switch ( t[++i] )
      {
        case '"':
          s[j] = 34;
          break;
        case '\'':
          s[j] = 39;
          break;
        case '?':
          s[j] = 63;
          break;
        case '\\':
          s[j] = 92;
          break;
        case 'a':
          s[j] = 7;
          break;
        case 'b':
          s[j] = 8;
          break;
        case 'f':
          s[j] = 12;
          break;
        case 'n':
          s[j] = 10;
          break;
        case 'r':
          s[j] = 13;
          break;
        case 't':
          s[j] = 9;
          break;
        case 'v':
          s[j] = 11;
          break;
        default:
          s[j++] = 92;
          s[j] = t[i];
          break;
      }
    }
    else
    {
      s[j] = t[i];
    }
    ++j;
  }
  s[j] = 0;
}