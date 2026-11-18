
char *strcpy2(char *dst, const char *src)
{
   char *dstSave=dst;
   int c;
   do
   {
      c = *dst++ = *src++;
   } while(c);
   return dstSave;
}
