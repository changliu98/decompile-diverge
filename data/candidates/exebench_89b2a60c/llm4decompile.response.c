char *char_replace( char *str, char old, char new )
{
 char *ch;

 if ( str == NULL )
  return NULL;

 if ( *str == '\0' )
  return str;

 ch = str;

 while ( ( ch = strchr( ch, old ) ) != NULL )
  *ch++ = new;

 return str;
}