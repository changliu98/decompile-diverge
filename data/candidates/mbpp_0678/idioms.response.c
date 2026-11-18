char *func0(char *str)
{
  int i; int j = 0;
  int len = strlen(str);
  for (i = 0; i < len; i++) {
    if (str[i] == ' ')
      continue;
    str[j++] = str[i];
  }
  str[j] = '\0';
  return str;
}