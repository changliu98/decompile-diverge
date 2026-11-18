void Q_bstrcpy( char *dest, const char *src ){
 while( *src ){
  *dest++ = *src++;
 }
 *dest = 0;
}