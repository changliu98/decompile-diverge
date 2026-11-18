void __cdecl copy2(char *s1, char *s2)
{
  char v2; // al

  while ( 1 )
  {
    v2 = *s2;
    *s1 = *s2;
    if ( !v2 )
      break;
    ++s1;
    ++s2;
  }
}