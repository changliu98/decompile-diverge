char *__cdecl smtp_stpcpy(char *s1, const char *s2)
{
  size_t v2; // rcx
  size_t i; // [rsp+0h] [rbp-18h]

  i = 0LL;
  do
  {
    s1[i] = s2[i];
    v2 = i++;
  }
  while ( s2[v2] );
  return &s1[i - 1];
}