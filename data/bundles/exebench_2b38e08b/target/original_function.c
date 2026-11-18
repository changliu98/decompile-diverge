static void copy_string( char *dst, char *src, int max )
{
   int i;

   for (i=0; i<max && (dst[i]=src[i]); i++)
     ;
}