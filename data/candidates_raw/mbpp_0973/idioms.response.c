char *rotate(char *str, int offset)
{
  int len = strlen(str);
  char *new = (char *)malloc((len + 1) * sizeof(char));
  int i;
  for (i = 0; i < len; i++)
    new[i] = str[(i + offset) % len];
  new[len] = '\0';
  return new;
}