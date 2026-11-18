int compter_mots(char *saisie, size_t *lenght)
{
   char *p = strchr(saisie, '\0');
   int words = 0, gui = 0;
   size_t lenght_current = 0,lenght_max = 0;
   p--;

   while(*p == ' ')
   {
      *p = '\0';
      p--;
   }
   p = saisie;
   while(*p == ' ')
      p++;
   if(*p != '\0')
      words++;
   for(;*p != '\0';p++)
   {
      if(*p == '"'||*p == '\'')
      {
  gui = (gui) ? 0 : 1;
  continue;
      }
      if((*p == ' ')&&(!gui))
      {
  if (lenght_current > lenght_max)
     lenght_max = lenght_current;
  lenght_current = 0;
  words++;
  while(*p == ' ')
     p++;
  p--;
  continue;
      }
      lenght_current++;
   }
   if (lenght_current > lenght_max)
      lenght_max = lenght_current;
   *lenght = lenght_max;
   return words;
}