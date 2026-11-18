char *func0(char *s, char *ct)
{
   char *save = s;

   for (;;ct++, s++)
      if (!(*s = *ct))
         break;

   *s = '\0';
   return save;
}