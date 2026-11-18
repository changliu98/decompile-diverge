char *__cdecl func0(const char *word)
{
  int i; // [rsp+Ch] [rbp-24h]

  for ( i = strlen(word) - 2; i >= 1; --i )
  {
    if ( strchr("AEIOUaeiou", word[i]) && !strchr("AEIOUaeiou", word[i + 1]) && !strchr("AEIOUaeiou", word[i - 1]) )
    {
      func0_out = word[i];
      return &func0_out;
    }
  }
  func0_out = 0;
  return &func0_out;
}