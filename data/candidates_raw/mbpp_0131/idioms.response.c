char *reverse_vowels(char *str)
{
  char *str1 = str;
  int i; int j = 0;
  char vowels[100];
  char c;
  memset(vowels,'\0',sizeof(vowels));
  for (i = 0; str1[i]; i++)
  {
    c = str1[i];
    if (strchr("aeiouAEIOU", c))
    {
      vowels[j++] = c;
    }
  }
  vowels[j] = '\0';
  j = 0;
  int k = strlen(vowels) - 1;
  for (i = 0; str1[i]; i++)
  {
    if (strchr("aeiouAEIOU", str1[i]))
    {
      str1[i] = vowels[k--];
    }
    result_string[j++] = str1[i];
  }
  result_string[j] = '\0';
  return result_string;
}