void __cdecl uc(char *buf)
{
  while ( *buf )
  {
    if ( *buf >= 97 && *buf <= 122 )
      *buf -= 32;
    ++buf;
  }
}