char *
char_replace (char *str, char o, char n)
{
   if (str == NULL || *str == '\0')
      return str;

   char *p = str;
   while ((p = strchr (p, o)) != NULL)
      *p++ = n;

   return str;
}