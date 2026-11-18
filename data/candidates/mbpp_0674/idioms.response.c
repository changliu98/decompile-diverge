char *func0(char *str)
{
  char *str1 = str;
  char *str2 = strdup(str);
  if (str2 == ((void *)0))
    return ((void *)0);
  char *unique[100];
  int unique_count = 0;
  char *word = strtok(str2, " ");
  while (word != ((void *)0))
  {
    int found = 0;
    int i;
    for (i = 0; i < unique_count; i++)
    {
      if (strcmp(word, unique[i]) == 0)
      {
        found = 1;
        break;
      }
    }
    if (!found)
      unique[unique_count++] = word;
    word = strtok(((void *)0), " ");
  }
  int total_length = 0;
  int i;
  for (i = 0; i < unique_count; i++)
    total_length += (strlen(unique[i]) + 1);
  char *ret = (char *)malloc(total_length);
  if (ret == ((void *)0))
  {
    free(str2);
    return ((void *)0);
  }
  ret[0] = '\0';
  for (i = 0; i < unique_count; i++)
  {
    strcat(ret, unique[i]);
    if (i < (unique_count - 1))
      strcat(ret, " ");
  }
  free(str2);
  return ret;
}