char *func0(char **strings, int count)
{
  int i; int length = 0;
  char *out;
  for (i = 0; i < count; i++)
    length += strlen(strings[i]);
  if ((out = (char *)malloc(length + 1)) == ((void *)0))
    return ((void *)0);
  out[0] = '\0';
  for (i = 0; i < count; i++)
    strcat(out, strings[i]);
  return (out);
}