void __cdecl snake_upcase_char(char *c)
{
  if ( *c < 97 || *c > 122 )
  {
    if ( *c == 45 )
      *c = 95;
  }
  else
  {
    *c &= ~0x20u;
  }
}