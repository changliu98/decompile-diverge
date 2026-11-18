char **get_words(char *text, int numc, int *returnSize)
{
  char **out = ((void *)0);
  int num = 0;
  int word = 0;
  int start = 0;
  unsigned long len = strlen(text);
  char *word_in_progress = (char *)malloc((len + 1)*sizeof(char));
  int i = 0;
  for (i = 0; i <= len; i++)
  {
    if (strchr(" \t\n\r\f\v",text[i]) || text[i] == '\0')
    {
      if (num == numc)
      {
        word_in_progress[i - start] = '\0';
        out = (char **)realloc(out, (word + 1)*sizeof(char *));
        out[word] = (char *)malloc((strlen(word_in_progress) + 1)*sizeof(char));
        strcpy(out[word], word_in_progress);
        word++;
      }
      start = i + 1;
      num = 0;
    }
    else
    {
      word_in_progress[i - start] = text[i];
      if (strchr("aeiouAEIOU",text[i]) == ((void *)0) && strchr(" \t\n\r\f\v",text[i]) == ((void *)0))
      {
        if (((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISalpha))
        {
          num++;
        }
      }
    }
  }
  free(word_in_progress);
  *returnSize = word;
  return out;
}