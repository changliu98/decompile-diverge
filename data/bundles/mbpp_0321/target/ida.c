char *__cdecl func0(const char *s)
{
  int i_0; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int pos; // [rsp+10h] [rbp-10h]
  int l; // [rsp+14h] [rbp-Ch]

  l = strlen(s);
  pos = 0;
  for ( i = 1; i <= l; ++i )
    pos += sprintf(&func0_res[pos], "%d", (unsigned int)i);
  for ( i_0 = l - 1; i_0 > 0; --i_0 )
    pos += sprintf(&func0_res[pos], "%d", (unsigned int)i_0);
  func0_res[pos] = 0;
  return func0_res;
}