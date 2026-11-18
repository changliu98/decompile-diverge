char *remove_words(char *str, int len)
{
  char temp_copy[-1];
  char *res = ((void *)0);
  char *token = ((void *)0);
  unsigned long res_len = 0;
  strncpy(temp_copy, str, 1000);
  temp_copy[1000 - 1] = '\0';
  res = (char *)malloc((strlen(str) + 1) * sizeof(char));
  if (res == ((void *)0))
  {
    perror("malloc failed");
    exit(1);
  }
  res[0] = '\0';
  token = strtok(temp_copy, " ");
  while (token != ((void *)0))
  {
    if (strlen(token) == len)
    {
      token = strtok(((void *)0), " ");
      continue;
    }
    strcat(res, token);
    strcat(res, " ");
    token = strtok(((void *)0), " ");
  }
  res_len = strlen(res);
  if (res_len > 0 && res[res_len - 1] == ' ')
  {
    res[res_len - 1] = '\0';
  }
  return res;
}