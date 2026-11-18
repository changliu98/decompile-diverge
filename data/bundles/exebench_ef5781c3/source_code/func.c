











char *strncpy2 ( char *target, char *source, int n )
{
   char *sp, *tp;
   int count;

   sp = source; tp = target; count = n;
   while ( count-- > 0 && *sp ) {
      *tp++ = *sp++ ;
   }
   *tp = '\0';

   return target;
}
