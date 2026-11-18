void __cdecl squeeze(char *s1, char *s2)
{
  int v2; // ecx
  int contains; // [rsp+0h] [rbp-20h]
  int k; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  i = 0;
  k = 0;
  while ( s1[i] )
  {
    contains = 0;
    for ( j = 0; s2[j]; ++j )
    {
      if ( s1[i] == s2[j] )
        contains = 1;
    }
    if ( !contains )
    {
      v2 = k++;
      s1[v2] = s1[i];
    }
    ++i;
  }
  s1[k] = 0;
}