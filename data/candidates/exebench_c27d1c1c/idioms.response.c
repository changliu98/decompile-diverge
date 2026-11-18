void reverse(char *str)
{
  char *start = str;
  char *end = str;
  char temp;
  if (str)
  {
    while(*end != '\0')
    {
      end++;
    }
    end--;
    while(start < end)
    {
      temp = *end;
      *end = *start;
      *start = temp;
      end--;
      start++;
    }
  }
}