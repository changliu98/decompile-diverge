static _Bool class_member(char c, char *class_start, char *class_end)
{
  _Bool is_member = 1;
  if (class_start[1] == '^')
  {
    is_member = 0;
    class_start++;
  }
  for (class_start++; class_start < class_end; class_start++)
  {
    if (class_start[1] == '%')
    {
      if (is_class_member(c, class_start[2]))
      {
        return is_member;
      }
    }
    else if (class_start[1] == '-' && class_start + 2 < class_end)
    {
      class_start += 2;
      if (c >= *class_start - 1 && c <= *class_start)
      {
        return is_member;
      }
    }
    else if (class_start[0] == c)
    {
      return is_member;
    }
  }
  return !is_member;
}