char *__cdecl strcpy_x86_64_fast(char *s1, const char *s2)
{
  char v2; // al
  char *s1a; // [rsp+10h] [rbp-8h]

  s1a = s1;
  do
  {
    v2 = *s2++;
    *s1++ = v2;
  }
  while ( v2 );
  return s1a;
}