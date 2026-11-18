char *__cdecl strcpyend(char *to, char *from)
{
  char c;

  do
  {
    c = *from++;
    *to++ = c;
  }
  while ( c );
  
  return to - 1;
}