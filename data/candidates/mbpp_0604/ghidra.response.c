char * func0(char *s)

{
  int i;
  char *token;
  char *words [10];
  int word_count;
  char *s_local;
  
  word_count = 0;
  token = strtok(s," ");
  while (token != (char *)0x0) {
    words[word_count] = token;
    token = strtok((char *)0x0," ");
    word_count = word_count + 1;
  }
  func0::result[0] = '\0';
  while (i = word_count + -1, -1 < i) {
    strcat(func0::result,words[i]);
    word_count = i;
    if (0 < i) {
      strcat(func0::result," ");
    }
  }
  return func0::result;
}