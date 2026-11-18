char *
substitute(char *string, char chold, char chnew)
{
 char *cp = string;

 if (cp)
  while (*cp) {
   if (*cp == chold) {
    *cp = chnew;
    break;
   }
   cp++;
  }
 return (string);
}