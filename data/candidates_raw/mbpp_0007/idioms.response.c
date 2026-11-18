char **get_words(char *text)
{
  char **words = (char **)malloc((strlen(text)/2 + 1)*sizeof(char *));
  int i = 0;
  char *copy = strdup(text);
  char *word = strtok(copy, " ");
  while (word != ((void *)0))
  {
    char *end = word + strlen(word) - 1;
    while (end > word && (*end == '.' || *end == ',' || *end == '!' || *end == '?' || *end == ';' || *end == ':'))
      *end-- = '\0';
    if (strlen(word) >= 4)
      words[i++] = strdup(word);
    word = strtok(((void *)0), " ");
  }
  words[i] = ((void *)0);
  free(copy);
  return words;
}