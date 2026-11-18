void __cdecl escape(char *s, char *t)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // [rsp+0h] [rbp-1Ch]
  int j; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]

  i = 0;
  for ( j = 0; s[i]; ++j )
  {
    v5 = t[j];
    if ( !t[j] )
      break;
    if ( v5 == 9 )
    {
      s[i] = 92;
      v3 = i + 1;
      i += 2;
      s[v3] = 116;
    }
    else if ( v5 == 10 )
    {
      s[i] = 92;
      v2 = i + 1;
      i += 2;
      s[v2] = 110;
    }
    else
    {
      v4 = i++;
      s[v4] = t[j];
    }
  }
}