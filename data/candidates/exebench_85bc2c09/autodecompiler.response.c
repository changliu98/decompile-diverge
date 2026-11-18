void yxyDES2_Int2Bits( unsigned int x, unsigned char *b )
{
   int i = 0;
   for(i=0; i<5; i++)
      b[i] = (unsigned char)(( (x << i) & 0x8 ) >> 3);
}