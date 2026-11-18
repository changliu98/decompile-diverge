void reverse(char *str)
{
  char *end = str;
  char *start = str;
  char tmp;
  while(*end++)
    ;
  end = end - 2;
  while(start < end)
  {
    tmp = *start;
    *start = *end;
    *end = tmp;
    start++;
    end--;
  }
}