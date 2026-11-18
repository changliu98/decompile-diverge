char **get_words(char *text, int *returnSize)
{
  int i;
  int j = 0;
  int num = 0;
  int count = 0;
  int len = strlen(text);
  char **out = ((void *)0);
  char word[100];
  memset(word, '\0', 100);
  if (strchr(text, ' ') || strchr(text, ','))
  {
    out = (char **)malloc((len + 1)*sizeof(char *));
    for (i = 0; i <= len; i++)
    {
      if (text[i] == ' ' || text[i] == ',' || text[i] == '\0')
      {
        if (j > 0)
        {
          word[j] = '\0';
          out[count] = (char *)strdup(word);
          count++;
          j = 0;
        }
      }
      else
      {
        word[j++] = text[i];
      }
    }
  }
  else
  {
    for (i = 0; i < len; i++)
    {
      if (((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISlower) && (text[i] - 'a') % 2 == 1)
      {
        num++;
      }
    }
    out = (char **)malloc((count + 1)*sizeof(char *));
    out[count] = (char *)malloc(sizeof(char)*12);
    sprintf(out[count], "%d", num);
    count++;
  }
  *returnSize = count;
  return out;
}