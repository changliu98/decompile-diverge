static int parse_matrix_header( char *buf, int *width, int *height,
 double *scale, double *offset )
{
 double p[4];
 char *q;
 char *p1;
 int i;

 if( (q = strchr(buf, '\r')) || (q = strchr(buf, '\n')) )
  *q = '\0';

 for( i = 0, p1 = buf; ; ) {
  char *next_p1;

  next_p1 = vips_break_token( p1, " \t" );
  if( !next_p1 && i < 5 )
   break;

  if( i < 5 ) {
   if( vips_strtod( p1, &p[i] ) ) {
    vips_error( "matload", "bad number \"%s\"", p1 );
    return( -1 );
   }
  }

  if( i >= 5 )
   break;

  i++;
  p1 = next_p1;
 }

 if( i < 5 )
  p[3] = 0;
 if( i < 4 )
  p[2] = 1;

 if( i < 3 ) {
  vips_error( "matload", "%s", "no width / height" );
  return( -1 );
 }

 if( floor(p[0]) != p[0] || floor(p[1]) != p[1] ) {
  vips_error( "mask2vips", "%s", "width / height not int" );
  return( -1 );
 }

 *width = p[0];
 *height = p[1];

 if( *width <= 0 || *width > 100000 ||
  *height <= 0 || *height > 100000 ) {
  vips_error( "mask2vips", "%s", "width / height out of range" );
  return( -1 );
 }

 if( p[2] == 0 ) {
  vips_error( "mask2vips", "%s", "zero scale" );
  return( -1 );
 }

 *scale = p[2];
 *offset = p[3];

 return( 0 );
}