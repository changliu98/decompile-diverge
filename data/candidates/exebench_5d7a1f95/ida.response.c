void __cdecl escape(char *s, char *t)
{
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  j = 0;
  for ( i = 0; t[i]; ++i )
  {
    switch ( t[i] )
    {
      case 7:
        s[j++] = 92;
        s[j] = 97;
        break;
      case 8:
        s[j++] = 92;
        s[j] = 98;
        break;
      case 9:
        s[j++] = 92;
        s[j] = 116;
        break;
      case 10:
        s[j++] = 92;
        s[j] = 110;
        break;
      case 11:
        s[j++] = 92;
        s[j] = 118;
        break;
      case 12:
        s[j++] = 92;
        s[j] = 102;
        break;
      case 13:
        s[j++] = 92;
        s[j] = 114;
        break;
      case 34:
        s[j++] = 92;
        s[j] = 34;
        break;
      case 39:
        s[j++] = 92;
        s[j] = 39;
        break;
      case 63:
        s[j++] = 92;
        s[j] = 63;
        break;
      case 92:
        s[j++] = 92;
        s[j] = 92;
        break;
      default:
        s[j] = t[i];
        break;
    }
    ++j;
  }
  s[j] = 0;
}