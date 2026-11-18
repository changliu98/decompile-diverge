char **func0(char *text, int *count)
{
  char *re = "\\b[a-zA-Z]{5}\\b";
  int i = 0;
  int len = strlen(text);
  char *buf = (char *)malloc(len + 1);
  strcpy(buf, text);
  int ret = regcomp(&re_word, re, 1);
  char *p = buf;
  while (regexec(&re_word, p, 1, &re_word_match, 0) == 0)
  {
    int start = re_word_match[0].rm_so;
    int end = re_word_match[0].rm_eo;
    char *word = (char *)malloc(end - start + 1);
    strncpy(word, p + start, end - start);
    word[end - start] = '\0';
    get_words_words[i++] = word;
    p += end;
  }
  regfree(&re_word);
  *count = i;
  return get_words_words;
}