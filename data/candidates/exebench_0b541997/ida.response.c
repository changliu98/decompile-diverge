void __cdecl lemon_strcpy(char *dest, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx

  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = dest++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
}