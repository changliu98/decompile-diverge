void Q_ParseNewlines( char *dest, const char *src, int destsize )
{
  for( ; *src && destsize > 1; src++, destsize-- )
    *dest++ = ( ( *src == '\\' && *( ++src ) == 'n' ) ? '\n' : *src );
  *dest++ = '\0';
}