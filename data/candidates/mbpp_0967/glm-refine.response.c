const char *__cdecl func0(const char *str)
{
  const char *vowels = "AEIOUaeiou";
  int found[10] = { 0 };
  int count = 0;

  // Iterate through the input string
  for (int i = 0; str[i]; ++i)
  {
    // Check the current character against all 10 vowels
    for (int j = 0; j < 10; ++j)
    {
      // If it's a match and we haven't counted this specific vowel yet
      if (str[i] == vowels[j] && !found[j])
      {
        found[j] = 1;
        ++count;
        break;
      }
    }
  }

  // If fewer than 5 unique vowels were found, return rejection string
  if (count < 5)
    return (const char *)&unk_200F; 
  
  return "accepted";
}