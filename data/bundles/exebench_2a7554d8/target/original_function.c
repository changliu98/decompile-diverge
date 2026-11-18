int replace(char *rps,char whatc, char toc)
{
   char *p1;
   p1=strchr(rps,whatc);
   while (p1) {
      *p1=toc;
      p1++;
      p1=strchr(p1,whatc);
   }
   return 0x0;
}