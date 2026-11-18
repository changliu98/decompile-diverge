void func0(char *str, char *alpha, char *result, char *palindrome)
{
  int i; int j; int k;
  int len = strlen(str);
  char *str2 = (char *)malloc((len + 1) * sizeof(char));
  for (i = k = 0; str[i]; i++)
  {
    char *ch = alpha;
    int found = 0;
    while (*ch)
    {
      if (str[i] == *ch)
      {
        found = 1;
        break;
      }
      ch++;
    }
    if (!found)
    {
      str2[k++] = str[i];
    }
  }
  str2[k] = '\0';
  len = strlen(str2);
  int is_palindrome = 1;
  for (i = 0; i < len / 2; i++)
  {
    if (str2[i] != str2[len - 1 - i])
    {
      is_palindrome = 0;
      break;
    }
  }
  strcpy(result, str2);
  strcpy(palindrome, is_palindrome ? "True" : "False");
  free(str2);
}