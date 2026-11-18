_Bool func0(char *brackets)

{
  int i;
  int level;
  char *brackets_local;
  
  level = 0;
  i = 0;
  while( true ) {
    if (brackets[i] == '\0') {
      return level == 0;
    }
    if (brackets[i] == '<') {
      level = level + 1;
    }
    if (brackets[i] == '>') {
      level = level + -1;
    }
    if (level < 0) break;
    i = i + 1;
  }
  return false;
}