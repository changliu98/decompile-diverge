int match(char *pat, int ch, int folded)
{
  char *p = pat;
  int last; int next;
  int complement = 0;
  if (*p == '!' || *p == '^')
  {
    complement = 1;
    ++p;
  }
  if (*p == ']')
  {
    if (ch == ']')
      return !complement;
    ++p;
  }
  else if (*p == '-')
  {
    if (ch == '-')
      return !complement;
    ++p;
  }
  last = *(p - 1);
  while (*p != ']')
  {
    if (*p == '-' && *(p + 1) != ']')
    {
      ++p;
      next = getnext(&p);
      if ((last <= ch && ch <= next) ||
          (last <= folded && folded <= next))
        return !complement;
    }
    else
    {
      next = getnext(&p);
      if (next == ch || next == folded)
        return !complement;
    }
  }
  return complement;
}