
const char*
copy_line( char *where, const char *what, int n )
{
  const char *now = what;
  int i = 0;


  while( ( i < n - 1 ) && *now && ( *now != '\n' ) && ( *now != '\r' ) )
  {
    *(where++) = *(now++);
    i++;
  }


  *where = '\0';


  if( *now=='\r' ) now++;
  if( *now=='\n' ) now++;

  return now;
}
