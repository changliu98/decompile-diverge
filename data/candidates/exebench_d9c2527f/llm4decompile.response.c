char *get_word(char *str, int *len)
{
 int i;
 char *p;

 i = 0;
 p = str;
 if (str == NULL)
  goto out;
 while (*p == '-')
  p++;
 if (*p < 'a' || *p > 'z')
  goto out;
 while (1)
 {
  if (i >= 64)
   break;
  if (p[i] >= '0' && p[i] <= '9')
   continue;
  if (p[i] >= 'a' && p[i] <= 'z')
   continue;
  if (p[i] == '-' || p[i] == '_')
   continue;
  break;
 }
out:
 *len = i;
 return (p);
}