char *__cdecl func0(const char *string)
{
  char *str;
  const char *token;
  char *unique[100];
  int unique_count;
  int i;
  int found;
  int total_length;
  char *result;

  str = strdup(string);
  if (!str)
    return NULL;

  unique_count = 0;
  for (token = strtok(str, " "); token; token = strtok(NULL, " "))
  {
    found = 0;
    for (i = 0; i < unique_count; ++i)
    {
      if (!strcmp(token, unique[i]))
      {
        found = 1;
        break;
      }
    }
    if (!found)
    {
      unique[unique_count] = (char *)token;
      unique_count++;
    }
  }

  total_length = 0;
  for (i = 0; i < unique_count; ++i)
    total_length += strlen(unique[i]) + 1;

  result = (char *)malloc(total_length);
  if (result)
  {
    *result = 0;
    for (i = 0; i < unique_count; ++i)
    {
      strcat(result, unique[i]);
      if (i < unique_count - 1)
        strcat(result, " ");
    }
  }

  free(str);
  return result;
}