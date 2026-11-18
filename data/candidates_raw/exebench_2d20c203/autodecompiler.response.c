char *my_revstr(char *str)
{
  char tmp;
  char *end;
  char *begin;

  begin = str;
  end = str;
  while (*end++ != '\0');
  end--;
  end--;
  while (begin < end)
    {
      tmp = *begin;
      *begin++ = *end;
      *end-- = tmp;
    }
  return (str);
}