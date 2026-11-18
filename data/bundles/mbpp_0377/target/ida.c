char *__cdecl func0(char *s, char c)
{
  size_t v2; // rax
  int i_0; // [rsp+8h] [rbp-28h]
  int j; // [rsp+Ch] [rbp-24h]
  char *result; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]
  int counts; // [rsp+20h] [rbp-10h]

  counts = 0;
  for ( i = 0; s[i]; ++i )
  {
    if ( s[i] == c )
      ++counts;
  }
  v2 = strlen(s);
  result = (char *)malloc(v2 - counts + 1);
  j = 0;
  for ( i_0 = 0; s[i_0]; ++i_0 )
  {
    if ( s[i_0] != c )
      result[j++] = s[i_0];
  }
  result[j] = 0;
  return result;
}