Corresponding numeric characters

void __cdecl numericCrypt(char *str)
{
  int charIndex;   // Index for the substitution alphabet
  int strIndex;    // Index for iterating over the input string

  // Iterate through each character in the input string until the null terminator
  for ( strIndex = 0; str[strIndex]; ++strIndex ) 
  {
    // Check the current character against the cipher alphabet
    for ( charIndex = 0; CIPHER_ALPHABET[charIndex]; ++charIndex ) 
    {
      // If a match is found, substitute the letter with its corresponding number
      if ( str[strIndex] == CIPHER_ALPHABET[charIndex] ) 
      {
        str[strIndex] = NUMERIC_ALPHABET[charIndex];
        break; // Move to the next character in the input string
      }
    }
  }
}