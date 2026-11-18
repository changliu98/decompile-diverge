void __cdecl strcpy_(char *dst, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax

  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = dst++;
    *v4 = v3;
  }
  *dst = 0;
}