void __cdecl numconv(char *numstr)
{
  char *v1; // rax

  while ( *numstr )
  {
    v1 = numstr++;
    *v1 -= 48;
  }
}