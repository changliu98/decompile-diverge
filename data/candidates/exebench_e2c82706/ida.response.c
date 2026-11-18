char *__cdecl strCpy(char *dest, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx
  char *desta; // [rsp+10h] [rbp-8h]

  desta = dest;
  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = desta++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return dest;
}