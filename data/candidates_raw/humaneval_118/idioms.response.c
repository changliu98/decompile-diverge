char *find_vowel(char *word)
{
  int i;
  for (i = strlen(word)-2; i >= 1; i--)
  {
    if (strchr("AEIOUaeiou", word[i]) && !strchr("AEIOUaeiou", word[i+1]) && !strchr("AEIOUaeiou", word[i-1]))
    {
      vowel = word[i];
      return (char *) &vowel;
    }
  }
  vowel = '\0';
  return (char *) &vowel;
}