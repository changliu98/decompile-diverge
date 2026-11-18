int compter_mots(char *saisie, size_t *lenght)
{
  int words;
  size_t lenght_current;
  size_t lenght_max;
  char *p;
  char guillemet;

  guillemet = 0;
  lenght_current = 0;
  lenght_max = 0;
  p = strchr(saisie, '\0');
  while (*(--p) == ' ')
    *p = '\0';
  p = saisie;
  while (*p == ' ')
    ++p;
  if (*p != '\0')
    words = 1;
  else
    words = 0;
  while (*p != '\0')
    {
      if (*p == '"' || *p == '\'')
 {
   guillemet = !guillemet;
 }
      else if (*p == ' ' && !guillemet)
 {
   if (lenght_current > lenght_max)
     lenght_max = lenght_current;
   lenght_current = 0;
   ++words;
   while (*p == ' ')
     ++p;
   --p;
 }
      else
 ++lenght_current;
      ++p;
    }
  if (lenght_current > lenght_max)
    lenght_max = lenght_current;
  *lenght = lenght_max;
  return (words);
}