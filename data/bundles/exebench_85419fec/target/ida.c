char *__cdecl strcpyend(char *to, char *from)
{
  char *v2; // rax
  char *v3; // rcx

  do
  {
    v2 = from++;
    LOBYTE(v2) = *v2;
    v3 = to++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return to - 1;
}