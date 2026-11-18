void __cdecl unescape(char *s, char *t)
{
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  j = 0;
  for ( i = 0; t[i]; ++i )
  {
    if ( t[i] == '\\' )
    {
      switch ( t[++i] )
      {
        case '"':
          s[j] = '"';
          break;
        case '\'':
          s[j] = '\'';
          break;
        case '?':
          s[j] = '?';
          break;
        case '\\':
          s[j] = '\\';
          break;
        case 'a':
          s[j] = '\a'; // Alert (bell)
          break;
        case 'b':
          s[j] = '\b'; // Backspace
          break;
        case 'f':
          s[j] = '\f'; // Form feed
          break;
        case 'n':
          s[j] = '\n'; // Newline
          break;
        case 'r':
          s[j] = '\r'; // Carriage return
          break;
        case 't':
          s[j] = '\t'; // Horizontal tab
          break;
        case 'v':
          s[j] = '\v'; // Vertical tab
          break;
        default:
          // If it's an unrecognized escape sequence, 
          // keep the backslash and the character as-is.
          s[j++] = '\\';
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
  s[j] = '\0'; // Null-terminate the destination string
}