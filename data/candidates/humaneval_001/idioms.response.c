char **func0(char *paren_string, int *group_count)
{
  int string_len = strlen(paren_string);
  int level = 0;
  int capacity = 10;
  char **groups = (char **)malloc(sizeof(char *) * capacity);
  char *buffer = (char *)malloc(string_len + 1);
  int buffer_index = 0;
  int i;
  *group_count = 0;
  for (i = 0; i < string_len; i++)
  {
    char c = paren_string[i];
    if (c == '(')
    {
      level++;
      buffer[buffer_index++] = c;
    }
    else if (c == ')')
    {
      level--;
      buffer[buffer_index++] = c;
      if (level == 0)
      {
        buffer[buffer_index] = '\0';
        groups[*group_count] = strdup(buffer);
        (*group_count)++;
        if (*group_count >= capacity)
        {
          capacity = capacity * 2;
          groups = (char **)realloc(groups, sizeof(char *) * capacity);
        }
        buffer_index = 0;
      }
    }
  }
  free(buffer);
  return groups;
}