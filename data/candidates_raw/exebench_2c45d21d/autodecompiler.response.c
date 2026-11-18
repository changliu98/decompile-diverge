char chop(char *string)
{
   char c, *s = string;
   if (!s || !*s)
      c = '\0';
   else
   {
      while (*s)
         s++;
      s--;
      c = *s;
      *s = '\0';
   }
   return(c);
}