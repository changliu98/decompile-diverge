void __cdecl copia(char *dest, const char *source)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax

  while ( *source )
  {
    v2 = source++;
    v3 = *v2;
    v4 = dest++;
    *v4 = v3;
  }
  *dest = 0;
}