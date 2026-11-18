char *__cdecl ft_strcpy(char *dest, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *desta; // [rsp+10h] [rbp-8h]

  desta = dest;
  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = desta++;
    *v4 = v3;
  }
  *desta = 0;
  return dest;
}