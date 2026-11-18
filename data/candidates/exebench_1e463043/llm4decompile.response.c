int
c_insensitive(char *a, char *b)
{
 int i;

 for (i = 0; a[i] != '\0'; i++)
  if (a[i] >= 'a' && a[i] <= 'z')
   a[i] -= 'a' - 'A';
 for (i = 0; b[i] != '\0'; i++)
  if (b[i] >= 'a' && b[i] <= 'z')
   b[i] -= 'a' - 'A';
 for (i = 0; a[i] != '\0' && b[i] != '\0'; i++)
  if (a[i] > b[i])
   return 1;
  else if (a[i] < b[i])
   return -1;
 return 0;
}