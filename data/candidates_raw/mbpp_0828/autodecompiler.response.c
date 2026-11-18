void analysis(char *str, int *a, int *d, int *s)
{
 int i;

 *a = *d = *s = 0;
 for (i = 0; ; i++) {
  if (!str[i]) break;
  else if (isalpha(str[i])) (*a)++;
  else if (isdigit(str[i])) (*d)++;
  else (*s)++;
 }
}