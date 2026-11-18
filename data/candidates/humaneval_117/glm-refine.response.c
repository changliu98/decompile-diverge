char **__cdecl func0(const char *s, int n, int *returnSize)
{
  char **out = NULL;
  int word_count = 0;
  int begin = 0;
  int consonant_count = 0;
  
  size_t length = strlen(s);
  char *current = (char *)malloc(length + 1);
  
  for (size_t i = 0; i <= length; ++i)
  {
    // If the character is not a space and not the null terminator
    if (!isspace(s[i]) && s[i] != '\0')
    {
      current[i - begin] = s[i];
      
      // If it's an alphabetic character and not a vowel, it's a consonant
      if (!strchr("aeiouAEIOU", s[i]) && isalpha(s[i]))
      {
        ++consonant_count;
      }
    }
    else
    {
      // End of a word is reached
      if (consonant_count == n)
      {
        current[i - begin] = '\0';
        out = (char **)realloc(out, sizeof(char *) * (word_count + 1));
        out[word_count] = (char *)malloc(strlen(current) + 1);
        strcpy(out[word_count], current);
        word_count++;
      }
      
      // Reset for the next word
      begin = i + 1;
      consonant_count = 0;
    }
  }
  
  free(current);
  *returnSize = word_count;
  return out;
}