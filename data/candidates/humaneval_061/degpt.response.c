_Bool func0(char *brackets)

{
  size_t sVar1;
  int i;
  int level;
  char *brackets_local;
  
  level = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(brackets);
    if (sVar1 <= (ulong)(long)i) {
      return level == 0;
    }
    if (brackets[i] == '(') {
      level = level + 1;
    }
    if (brackets[i] == ')') {
      level = level + -1;
    }
    if (level < 0) break;
    i = i + 1;
  }
  return false;
}