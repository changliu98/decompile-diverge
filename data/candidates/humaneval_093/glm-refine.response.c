void __cdecl func0(const char *text, char *result)
{
  const char *vowels = "AEIOUaeiou";
  char ch;
  int j;
  int i;

  for (i = 0; text[i] != '\0'; ++i)
  {
    ch = text[i];

    // Toggle case based on character type
    if (isspace(ch))
    {
      ch = toupper(ch);
    }
    else if (ispunct(ch))
    {
      ch = tolower(ch);
    }

    // Check if the character is a vowel
    for (j = 0; vowels[j] != '\0'; ++j)
    {
      if (ch == vowels[j])
      {
        // If it's an uppercase vowel (indices 0-9), shift character by 2
        if (j < 10)
          ch += 2;
        break;
      }
    }
    
    result[i] = ch;
  }
  
  result[i] = '\0';
}