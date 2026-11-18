char **__cdecl func0(const char *s, int *count)
{
  int capacity = 10;
  char **out = (char **)malloc(8LL * capacity); // 8 bytes per pointer * 10
  size_t len = strlen(s);
  char *current = (char *)malloc(len + 1);
  int word_count = 0;
  int current_length = 0;

  for (int i = 0; s[i]; ++i)
  {
    if (s[i] == ' ' || s[i] == ',')
    {
      if (current_length > 0)
      {
        current[current_length] = '\0';
        out[word_count++] = strdup(current);
        current_length = 0;
        
        if (word_count >= capacity)
        {
          capacity *= 2;
          out = (char **)realloc(out, 8LL * capacity);
        }
      }
    }
    else
    {
      current[current_length++] = s[i];
    }
  }

  // Handle the last word if the string doesn't end with a delimiter
  if (current_length > 0)
  {
    current[current_length] = '\0';
    out[word_count++] = strdup(current);
  }

  free(current);
  *count = word_count;
  return out;
}