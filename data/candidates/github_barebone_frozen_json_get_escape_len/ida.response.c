int __cdecl json_get_escape_len(const char *s, int len)
{
  int v2; // eax
  int v3; // eax
  bool v5; // [rsp+Bh] [rbp-25h]
  int v6; // [rsp+Ch] [rbp-24h]
  int v7; // [rsp+2Ch] [rbp-4h]

  switch ( *s )
  {
    case '"':
    case '/':
    case '\\':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
      v3 = 1;
      if ( len < 2 )
        v3 = -2;
      v7 = v3;
      break;
    case 'u':
      if ( len >= 6 )
      {
        v5 = 0;
        if ( json_isxdigit(s[1]) )
        {
          v5 = 0;
          if ( json_isxdigit(s[2]) )
          {
            v5 = 0;
            if ( json_isxdigit(s[3]) )
              v5 = json_isxdigit(s[4]) != 0;
          }
        }
        v2 = -1;
        if ( v5 )
          v2 = 5;
        v6 = v2;
      }
      else
      {
        v6 = -2;
      }
      v7 = v6;
      break;
    default:
      v7 = -1;
      break;
  }
  return v7;
}