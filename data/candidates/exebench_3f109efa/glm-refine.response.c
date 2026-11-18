void __cdecl ceasar(char *text, char offset)
{
  int j;
  unsigned int i;

  for (i = 0; text[i] != '\0'; ++i)
  {
    // Check if the character is an uppercase or lowercase letter
    if ((text[i] > 'A' && text[i] < 'Z') || (text[i] > 'a' && text[i] < 'z'))
    {
      // Apply the shift 'offset' times
      for (j = 0; j < offset; ++j)
      {
        // Wrap around from 'Z' to 'A'
        if (text[i] == 'Z')
        {
          text[i] = 'A';
          --text[i];
        }
        // Wrap around from 'z' to 'a'
        if (text[i] == 'z')
        {
          text[i] = 'a';
          --text[i];
        }
        // Shift the character by one
        ++text[i];
      }
    }
  }
}