char *__cdecl func0(char *text1)
{
  int v1; // ecx
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  i = 0;
  j = 0;
  while ( text1[i] )
  {
    if ( ((*__ctype_b_loc())[(unsigned __int8)text1[i]] & 0x2000) == 0 )
    {
      v1 = j++;
      text1[v1] = text1[i];
    }
    ++i;
  }
  text1[j] = 0;
  return text1;
}