void toUpper(char *str)
{
  for ( ; *str != '\0'; str++ )
  {
    if ( *str == 't' )
      *str = 'u';
    else if ( *str == 'T' )
      *str = 'U';
  }
}