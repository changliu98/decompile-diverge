char *__cdecl strcpy(char *dest, const char *src)
{
  char v2; // al
  char *desta; // [rsp+14h] [rbp-8h]

  desta = dest;
  do
  {
    v2 = *src++;
    *dest++ = v2;
  }
  while ( v2 );
  return desta;
}