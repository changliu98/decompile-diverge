void __cdecl gdb_strcpy(char *buf, const char *s)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax

  while ( *s )
  {
    v2 = s++;
    v3 = *v2;
    v4 = buf++;
    *v4 = v3;
  }
  *buf = 0;
}