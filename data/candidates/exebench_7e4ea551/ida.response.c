void __cdecl inplace_strcpy(char *to, const char *from)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax

  while ( *from )
  {
    v2 = from++;
    v3 = *v2;
    v4 = to++;
    *v4 = v3;
  }
  *to = *from;
}