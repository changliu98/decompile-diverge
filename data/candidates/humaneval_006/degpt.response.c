int * func0(char *paren_string,int *returnSize)

{
  char chr;
  int count;
  int i;
  int max_level;
  int level;
  int *all_levels;
  int *returnSize_local;
  char *paren_string_local;
  
  all_levels = (int *)0x0;
  level = 0;
  max_level = 0;
  count = 0;
  for (i = 0; paren_string[i] != '\0'; i = i + 1) {
    if (paren_string[i] == '(') {
      level = level + 1;
      if (max_level < level) {
        max_level = level;
      }
    }
    else if ((paren_string[i] == ')') && (level = level + -1, level == 0)) {
      all_levels = realloc(all_levels,(long)(count + 1) << 2);
      all_levels[count] = max_level;
      max_level = 0;
      count = count + 1;
    }
  }
  *returnSize = count;
  return all_levels;
}