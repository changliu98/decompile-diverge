void GetWord(char *word, char *line, int max) {
  int i = 0;
  while (*line <= ' ' && *line > 0) line++;
  while (*line > ' ' || *line < 0) {
    if (i >= max - 1) break;
    *word++ = *line++;
    i++;
  }
  *word = 0;
}