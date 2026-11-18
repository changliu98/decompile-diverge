char *__cdecl string_copy(char *dest, const char *a)
{
  char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *d; // [rsp+0h] [rbp-28h]
  char *s; // [rsp+8h] [rbp-20h]

  if ( !a || !dest )
    return 0LL;
  s = (char *)a;
  d = dest;
  while ( *s )
  {
    v2 = s++;
    v3 = *v2;
    v4 = d++;
    *v4 = v3;
  }
  *d = 0;
  return dest;
}