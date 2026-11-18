char *get_word(char *id, int *len)
{
 char *ret = id;
 int i = 0;
 if (id)
 {
  while (id[0] == '-')
   id++;
  if (id[0] >= 'a' && id[0] <= 'z')
  {
   for (;;)
   {
    char bit = 0;
    if (i < 64)
    {
     char ok = 1;
     if (id[i] >= '0' && id[i] <= '9')
      ok = 1;
     else if (id[i] >= 'a' && id[i] <= 'z')
      ok = 1;
     else
      ok = (id[i] == '-' || id[i] == '_');
     bit = ok;
    }
    if (!bit)
     break;
    i++;
   }
  }
 }
 *len = i;
 return ret;
}