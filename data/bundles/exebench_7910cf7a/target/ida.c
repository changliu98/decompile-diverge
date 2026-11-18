char *__cdecl strset(char *str, int c)
{
  char *v2; // rax
  char *s; // [rsp+0h] [rbp-18h]

  for ( s = str; *s; ++s )
  {
    v2 = s;
    *v2 = c;
  }
  return str;
}