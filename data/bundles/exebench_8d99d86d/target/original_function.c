void decode6( long v, long width, long height, long *x, long *y )
{
 long w;
  long D=6;
  long col = v / (height*6);
 long maxcol = (width-4)/6;
 if ( col>=maxcol )
 {
  col=maxcol;
  D = width-maxcol*6;
 }
 w = v - (col * height * 6 );

  *x = col*6 + (w%D);
 *y = height-1 - (w/D);
}