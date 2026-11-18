char *func0(int n, char **test_list)
{
  int i;
  int j;
  int k;
  int unique;
  int found;
  int found_word;
  int max;
  int index;
  char word[50];
  char *test;
  char *test_list_item;
  test_list_item = test_list;
  unique = 0;
  for (i = 0; i < n; i++)
  {
    test = test_list_item[i];
    j = 0;
    while (*test != '\0')
    {
      if (((*__ctype_b_loc ())[(int) ((*test))] & (unsigned short) _ISspace))
      {
        if (j > 0)
        {
          word[j] = '\0';
          found = 0;
          for (k = 0; k < unique; k++)
          {
            if (strcmp(func0_words[k].word, word) == 0)
            {
              func0_words[k].count++;
              found = 1;
              break;
            }
          }
          if (!found)
          {
            strcpy(func0_words[unique].word, word);
            func0_words[unique].count = 1;
            unique++;
          }
          j = 0;
        }
      }
      else
      {
        word[j++] = *test;
      }
      test++;
    }
    if (j > 0)
    {
      word[j] = '\0';
      found_word = 0;
      for (k = 0; k < unique; k++)
      {
        if (strcmp(func0_words[k].word, word) == 0)
        {
          func0_words[k].count++;
          found_word = 1;
          break;
        }
      }
      if (!found_word)
      {
        strcpy(func0_words[unique].word, word);
        func0_words[unique].count = 1;
        unique++;
      }
    }
  }
  max = 0;
  index = 0;
  for (i = 0; i < unique; i++)
  {
    if (func0_words[i].count > max)
    {
      max = func0_words[i].count;
      index = i;
    }
  }
  return (char *)func0_words[index].word;
}