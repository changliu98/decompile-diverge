char *Q_strupr (char *str)
{
 char* origs = str;
 while (*str) {
  if (*str >= 'a' && *str <= 'z')
   *str -= 'a' - 'A';
  str++;
 }
 return origs;
}