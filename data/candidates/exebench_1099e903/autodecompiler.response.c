void set_nb(char *str, char delim, int *count)
{
 int i;
 int j;

 j = 0;
 i = 0;
 while (str[j] != '\0')
 {
  if (j == i && str[j] == delim)
  {
   j++;
   i++;
  }
  else if (str[i] == delim || str[i] == '\0')
  {
   *count += 1;
   j = i;
  }
  else
   i++;
 }
}