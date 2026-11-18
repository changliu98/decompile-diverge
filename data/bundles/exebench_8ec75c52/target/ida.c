void __cdecl strupr(char *str)
{
  while ( *str )
  {
    if ( *str >= 97 && *str <= 122 )
      *str -= 32;
    ++str;
  }
}