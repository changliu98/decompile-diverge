char *__cdecl func0(char *str1)
{
  int v1; // ecx
  int len; // [rsp+Ch] [rbp-14h]
  int j; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]

  j = 0;
  len = strlen(str1);
  for ( i = 0; i < len; ++i )
  {
    if ( str1[i] != 32 )
    {
      v1 = j++;
      str1[v1] = str1[i];
    }
  }
  str1[j] = 0;
  return str1;
}