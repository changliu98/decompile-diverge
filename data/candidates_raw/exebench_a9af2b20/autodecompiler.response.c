char *strcpy(char *s1, const char *s2)
{
   char *s = s1;
   while (1)
   {
      *s1 = *s2;
      if (*s2 == '\0')
         return(s);
      s1++;
      s2++;
   }
}