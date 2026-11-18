int count_vowels(char *word)
{
  int count = 0;
  int length = strlen(word);
  int i;
  for (i = 0; i < length; i++)
  {
    if (strchr("aeiouAEIOU", word[i]) != ((void *)0))
    {
      count++;
    }
  }
  if (length > 0 && (word[length - 1] == 'y' || word[length - 1] == 'Y'))
  {
    count++;
  }
  return count;
}