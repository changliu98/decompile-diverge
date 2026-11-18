void reverse(char *str)
{
  char *end = str;
  char *start = str;
  while(*end++)
    ;
  end -= 2;
  while(start < end)
  {
    *start ^= *end;
    *end ^= *start;
    *start ^= *end;
    start++;
    end--;
  }
}