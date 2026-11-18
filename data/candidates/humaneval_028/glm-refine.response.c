char *func0(char **strings, int count)
{
  int total_length = 0;
  for (int i = 0; i < count; ++i)
    total_length += strlen(strings[i]);

  char *out = (char *)malloc(total_length + 1);
  if (!out)
    return NULL;

  *out = '\0';
  for (int i = 0; i < count; ++i)
    strcat(out, strings[i]);

  return out;
}