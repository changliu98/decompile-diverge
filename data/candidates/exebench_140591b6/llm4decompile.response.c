void Q_ParseNewlines( char *dest, const char *src, int destsize )
{
 while( *src && destsize > 1 )
 {
  if( *src == '\\' && *(src+1) == 'n' )
  {
   *dest++ = '\n';
   src += 2;
  }
  else
  {
   *dest++ = *src++;
  }
  destsize--;
 }
 *dest = 0;
}