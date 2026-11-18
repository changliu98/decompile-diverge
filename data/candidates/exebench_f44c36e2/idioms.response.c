void strcpymax(char *dest, char *src, int n)
{
  int i;
  if ( n )
  {
    for ( i = 0; ; i++ )
    {
      int copy = 0;
      if ( *src )
        copy = i < n - 1;
      if ( !copy )
        break;
      *dest++ = *src++;
    }
  }
  *dest = '\0';
}