char **split(char *text, int *count)
{
  int i;
  int len = strlen(text);
  char **words = (char **)malloc(len * sizeof(char *));
  *count = 0;
  int word_start = 0;
  for (i = 1; i <= len; i++)
  {
    if (i == len || (((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISupper) && !(((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISupper)))
    {
      words[*count] = (char *)malloc((i - word_start + 1) * sizeof(char));
      strncpy(words[*count], &text[word_start], i - word_start);
      words[*count][i - word_start] = '\0';
      (*count)++;
      word_start = i;
    }
  }
  return words;
}