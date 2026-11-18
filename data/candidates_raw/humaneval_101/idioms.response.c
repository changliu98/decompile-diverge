char **split(char *text, int *count)
{
  int capacity = 10;
  int i;
  char **words = (char **)malloc(sizeof(char *) * capacity);
  char *current = (char *)malloc(sizeof(char) * (strlen(text) + 1));
  int word_count = 0;
  int current_length = 0;
  for (i = 0; text[i]; i++)
  {
    if (text[i] == ' ' || text[i] == ',')
    {
      if (current_length > 0)
      {
        current[current_length] = '\0';
        words[word_count++] = strdup(current);
        current_length = 0;
        if (word_count >= capacity)
        {
          capacity *= 2;
          words = (char **)realloc(words, sizeof(char *) * capacity);
        }
      }
    }
    else
    {
      current[current_length++] = text[i];
    }
  }
  if (current_length > 0)
  {
    current[current_length] = '\0';
    words[word_count++] = strdup(current);
  }
  free(current);
  *count = word_count;
  return words;
}