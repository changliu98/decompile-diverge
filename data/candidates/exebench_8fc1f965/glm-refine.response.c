void __cdecl murcielagoCrypt(char *str)
{
  int keyIndex;    // Replaces letterIndex
  int strIndex;    // Replaces strIndex

  // Iterate over each character in the input string until the null terminator
  for ( strIndex = 0; str[strIndex]; ++strIndex )
  {
    // Iterate over the cipher key ("murcielago...") to find a match
    for ( keyIndex = 0; aMurcielagomurc[keyIndex]; ++keyIndex )
    {
      // If the current character matches a character in the key
      if ( str[strIndex] == aMurcielagomurc[keyIndex] )
      {
        // Substitute the character with the corresponding character 
        // from the substitution string ("0123456789...")
        str[strIndex] = a01234567890123[keyIndex];
        
        // Break out of the inner loop to prevent further substitution 
        // on the same character (1-to-1 mapping)
        break;
      }
    }
  }
}