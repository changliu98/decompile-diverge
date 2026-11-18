
void short_to_string( char* res, unsigned short s ){
  unsigned char c;
  unsigned short r = 0;


  c = (( s - r ) / 10000 );
  r = r + ( c * 10000 );
  *res++ = c + 0x30;


  c = (( s - r ) / 1000 );
  r = r + ( c * 1000 );
  *res++ = c + 0x30;


  c = (( s - r ) / 100 );
  r = r + ( c * 100 );
  *res++ = c + 0x30;


  c = (( s - r ) / 10 );
  r = r + ( c * 10 );
  *res++ = c + 0x30;


  c = (( s - r ) );
  r = r + ( c );
  *res++ = c + 0x30;

  *res++ = '\0';
}
