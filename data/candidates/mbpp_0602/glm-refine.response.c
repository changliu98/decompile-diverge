char __cdecl func0(const char *str)
{
  int length = strlen(str);

  for (int i = 0; i < length; ++i)
  {
    int count = 0;
    
    // Count occurrences of str[i] in the substring str[0...i]
    for (int j = 0; j <= i; ++j)
    {
      if (str[j] == str[i])
        ++count;
    }
    
    // If the character appears more than once up to index i, 
    // it is the first recurring character.
    if (count > 1)
      return str[i];
  }
  
  return '0'; // ASCII 48
}