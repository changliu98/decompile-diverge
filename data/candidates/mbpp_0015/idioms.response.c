char **func0(char *text, int *count)
{
  int len = 0;
  int i;
  char *word;
  char **words = ((void *)0);
  *count = 0;
  len = strlen(text);
  for (i = 0; i < len; i++)
  {
    if ( ((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISlower))
    {
      int start = i;
      i++;
      while (1)
      {
        char c = 0;
        if (i < len)
        {
          c = !((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISlower);
        }
        if (c & 1)
        {
          i++;
        }
        else
        {
          break;
        }
      }
      word = (char *)malloc(sizeof(char) * (i - start + 1));
      strncpy(word, &text[start], i - start);
      word[i - start] = '\0';
      words = (char **)realloc(words, (sizeof(char *) * (*count + 1)));
      words[*count] = word;
      (*count)++;
    }
  }
  return words;
}