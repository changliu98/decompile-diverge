char *__cdecl func0(char **strings, int count)
{
  int i_0; // [rsp+4h] [rbp-2Ch]
  char *out; // [rsp+8h] [rbp-28h]
  int i; // [rsp+14h] [rbp-1Ch]
  int length; // [rsp+18h] [rbp-18h]

  length = 0;
  for ( i = 0; i < count; ++i )
    length += strlen(strings[i]);
  out = (char *)malloc(length + 1);
  if ( !out )
    return 0LL;
  *out = 0;
  for ( i_0 = 0; i_0 < count; ++i_0 )
    strcat(out, strings[i_0]);
  return out;
}