char *str_copy(char *str, char *copy)
{
 int len = strlen(str);
 int i;
 for (i = 0; i < len; i++)
  copy[i] = str[i];
 copy[len] = '\0';
 return copy;
}