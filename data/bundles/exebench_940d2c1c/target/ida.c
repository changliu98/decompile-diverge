void __cdecl escape(char *s1, char *s2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // [rsp+0h] [rbp-1Ch]
  int j; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]

  j = 0;
  for ( i = 0; s2[i]; ++i )
  {
    v6 = s2[i];
    switch ( v6 )
    {
      case 9:
        v3 = j++;
        s1[v3] = 92;
        s1[j] = 116;
        break;
      case 10:
        v2 = j++;
        s1[v2] = 92;
        s1[j] = 110;
        break;
      case 34:
        v5 = j++;
        s1[v5] = 92;
        s1[j] = 34;
        break;
      case 92:
        v4 = j++;
        s1[v4] = 92;
        s1[j] = 92;
        break;
      default:
        s1[j] = s2[i];
        break;
    }
    ++j;
  }
  s1[j] = s2[i];
}