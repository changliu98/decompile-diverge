void __cdecl strcpy4(char *s, char *t)
{
  char *v2; // rax
  char *v3; // rcx

  do
  {
    v2 = t++;
    LOBYTE(v2) = *v2;
    v3 = s++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
}