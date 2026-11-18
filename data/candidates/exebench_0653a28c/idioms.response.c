void reverse(char *str)
{
  char *end = str;
  char *begin = str;
  char tmp;
  while(*end++)
    ;
  end -= 2;
  while(begin < end)
  {
    tmp = *begin;
    *begin = *end;
    *end = tmp;
    begin++;
    end--;
  }
}