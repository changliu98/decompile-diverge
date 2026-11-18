int filter(char **strings, int count, char *prefix, char ***out)
{
  int prefix_len = strlen(prefix);
  int i;
  *out = (char **)malloc(count * sizeof(char *));
  int out_count = 0;
  for (i = 0; i < count; i++) {
    if (strncmp(strings[i], prefix, prefix_len) == 0)
      (*out)[out_count++] = strings[i];
  }
  return out_count;
}