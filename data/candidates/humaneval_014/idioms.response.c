char **func0(char *str, int *count)
{
  int len = strlen(str);
  char **out = (char **)malloc(len * sizeof(char *));
  char *current = (char *)malloc((len + 1) * sizeof(char));
  int i;
  current[0] = '\0';
  for (i = 0; i < len; i++)
  {
    int current_len = strlen(current);
    current = (char *)realloc(current, (current_len + 2) * sizeof(char));
    current[current_len] = str[i];
    current[current_len + 1] = '\0';
    out[i] = (char *)malloc((strlen(current) + 1) * sizeof(char));
    strcpy(out[i], current);
  }
  free(current);
  *count = len;
  return out;
}