void BMP_getGenBmp16Palette( unsigned short *src, unsigned short *dest )
{
 unsigned short *spal = src + 1;
 unsigned short *dpal = dest;
 unsigned short i;

 i = 16;
 while( i-- )
 {
  *dpal++ = *spal++;
 }
}