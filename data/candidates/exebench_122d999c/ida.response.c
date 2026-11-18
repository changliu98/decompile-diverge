char *__cdecl mystpcpy(char *dest, char *src)
{
  char *v2; // rax
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