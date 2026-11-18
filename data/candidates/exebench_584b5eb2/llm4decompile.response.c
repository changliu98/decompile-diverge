char *substitute(char *string, char chold, char chnew)
{
  char *ptr;

  if (string)
    for (ptr = string; *ptr != '\0'; ptr++)
      if (*ptr == chold)
 {
   *ptr = chnew;
   break;
 }
  return string;
}