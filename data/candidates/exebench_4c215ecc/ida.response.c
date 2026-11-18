char *__cdecl stpcpy0(char *dest, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax

  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = dest++;
    *v4 = v3;
  }
  *dest = 0;
  return dest;
}