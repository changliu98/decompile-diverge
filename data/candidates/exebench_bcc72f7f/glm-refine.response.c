void __cdecl decrypt(char *string, int shift)
{
  // Iterate through the string until the null terminator is reached
  for (int i = 0; string[i] != '\0'; ++i)
  {
    // Replace hyphens with spaces
    if (string[i] == '-')
    {
      string[i] = ' ';
    }
    else
    {
      // Normalize the shift to handle values larger than 26 or negative shifts
      int normalized_shift = shift % 26;
      
      // Perform a Caesar cipher shift on the lowercase alphabet
      // 'a' (97) is subtracted to make the letter 0-indexed, then added back after the modulo
      string[i] = ((string[i] - 'a' + normalized_shift) % 26) + 'a';
    }
  }
}