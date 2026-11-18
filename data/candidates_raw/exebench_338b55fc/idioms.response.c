void reverse(char *str)
{
  char *start = str;
  char *end = str;
  while(*end != '\0')
  {
    end++;
  }
  end--;
  while(start < end)
  {
    *start = *start ^ *end;
    *end = *start ^ *end;
    *start = *start ^ *end;
    start++;
    end--;
  }
  return;
}