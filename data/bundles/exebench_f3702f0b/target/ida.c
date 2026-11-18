void __cdecl escape(char *s, char *t)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // [rsp+0h] [rbp-1Ch]
  int j; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]

  j = 0;
  for ( i = 0; t[i]; ++i )
  {
    v6 = t[i];
    switch ( v6 )
    {
      case 9:
        s[j] = 92;
        v4 = j + 1;
        j += 2;
        s[v4] = 116;
        break;
      case 10:
        s[j] = 92;
        v3 = j + 1;
        j += 2;
        s[v3] = 110;
        break;
      case 32:
        s[j] = 92;
        v2 = j + 1;
        j += 2;
        s[v2] = 98;
        break;
      default:
        v5 = j++;
        s[v5] = t[i];
        break;
    }
  }
  s[j] = 0;
}