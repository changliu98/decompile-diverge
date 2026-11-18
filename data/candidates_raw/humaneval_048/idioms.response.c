int is_palindrome(char *text)
{
  int len = strlen(text);
  int i;
  for (i = 0; i < len / 2; i++)
  {
    if (text[i] != text[len - 1 - i])
    {
      return 0;
    }
  }
  return 1;
}