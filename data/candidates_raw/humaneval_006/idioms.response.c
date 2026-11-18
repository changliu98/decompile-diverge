int *get_all_levels(char *paren_string, int *returnSize)
{
  int *all_levels = ((void *)0);
  int level = 0;
  int max_level = 0;
  int i;
  int count = 0;
  for (i = 0; paren_string[i] != '\0'; i++)
  {
    char c = paren_string[i];
    if (c == '(')
    {
      level++;
      if (level > max_level)
      {
        max_level = level;
      }
    }
    else if (c == ')')
    {
      level--;
      if (level == 0)
      {
        all_levels = (int *) realloc(all_levels, (count + 1) * sizeof(int));
        all_levels[count++] = max_level;
        max_level = 0;
      }
    }
  }
  *returnSize = count;
  return all_levels;
}