void strip(char *str)
{
 int i, j, k;

 if (str == NULL)
  return;

 for (i = 1; str[i] != '\0'; i++)
  for (j = 0; j < i; j++)
   if (str[j] == str[i]) {
    str[i] = -1;
    break;
   }

 for (i = 1; str[i] != '\0'; i++)
  if (str[i] == -1) {
   for (j = i; str[j] == -1; j++);
   for (k = i; str[j] != '\0'; k++, j++)
    if (str[j] != -1) {
     str[k] = str[j];
     str[j] = -1;
    }
   str[k] = '\0';
   break;
  }
}