char *__cdecl ft_strcpy(char *dst, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *dsta; // [rsp+10h] [rbp-8h]

  dsta = dst;
  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = dsta++;
    *v4 = v3;
  }
  *dsta = 0;
  return dst;
}