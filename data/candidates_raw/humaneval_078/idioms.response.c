int count(char *str)
{
  int count = 0;
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (strchr("2357BD", str[i]) != ((void *)0)) {
      count++;
    }
  }
  return count;
}