char** func0(const char* text, int* count) {
  regex_t regex;
  regmatch_t matches[1];
  static char* words[10];
  char pattern[] = "\\b[a-zA-Z]{5}\\b";
  int word_count = 0;
  char str[strlen(text) + 1];
  strcpy(str, text);
  regcomp(&regex, pattern, REG_EXTENDED);
  char* p = str;
  while (regexec(&regex, p, 1, matches, 0) == 0) {
    int start = matches[0].rm_so;
    int end = matches[0].rm_eo;
    char* word = (char*)malloc(sizeof(char) * (end - start + 1));
    strncpy(word, p + start, end - start);
    word[end - start] = '\0';
    words[word_count++] = word;
    p += end;
  }
  regfree(&regex);
  *count = word_count;
  return words;
}