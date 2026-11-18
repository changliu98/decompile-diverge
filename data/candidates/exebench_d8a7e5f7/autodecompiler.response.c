int ExtractRnick(char *buf, char *nick)
{
 int i = 0;
 int j;

 if (*nick == ':')
  nick++;

 while (1)
 {
  char c = !(*nick == '!' || *nick == '\0');

  if (!c)
   break;

  buf[i] = *nick;
  nick++;
  i++;
 }

 buf[i] = '\0';

 if (buf[0] < '0')
  j = 0;
 else
  j = 1;

 return j;
}