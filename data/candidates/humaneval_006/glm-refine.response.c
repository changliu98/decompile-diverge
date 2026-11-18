int *func0(const char *paren_string, int *returnSize)
{
  char chr;
  int count = 0;
  int i;
  int max_level = 0;
  int level = 0;
  int *all_levels = NULL;

  for (i = 0; paren_string[i]; ++i)
  {
    chr = paren_string[i];
    
    // chr == '('
    if (chr == 40)
    {
      if (++level > max_level)
        max_level = level;
    }
    // chr == ')'
    else if (chr == 41 && !--level)
    {
      all_levels = (int *)realloc(all_levels, 4LL * (count + 1));
      all_levels[count++] = max_level;
      max_level = 0;
    }
  }
  
  *returnSize = count;
  return all_levels;
}