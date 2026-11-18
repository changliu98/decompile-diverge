char *strcpyend(char *to, char *from)
{
  register char *to1 = to;
  register char *from1 = from;
  for ( ; ( *to1++ = *from1++ ) != '\0'; )
    ;
  return ( to - 1 );
}