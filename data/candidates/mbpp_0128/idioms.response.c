char **func0(int n, char *str, int *count)
{
  char *word;
  int i = 0;
  for (word = strtok(str, " "); word != ((void *)0); word = strtok(((void *)0), " "))
  {
    if (strlen(word) > n)
      word_len[i++] = word;
  }
  *count = i;
  return word_len;
}