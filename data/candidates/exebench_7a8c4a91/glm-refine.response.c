void __cdecl removeCharactersInPlace(char *aString, char *excludeChars)
{
  char *writePtr = aString;
  char *readPtr = aString;

  // Iterate through the string until the null terminator
  while (*readPtr)
  {
    char *excludePtr = excludeChars;
    char found = 0;

    // Check if the current character matches any of the exclude characters
    do
    {
      found = (*readPtr == *excludePtr++);
      char v2 = 0;
      if (*excludePtr)
        v2 = ~found;

      // Continue looping only if we haven't found a match and haven't reached the end of excludeChars
      if (!((v2 & 1) != 0))
        break;
    } 
    while (1);

    // If the character was not found in excludeChars, keep it
    if ((found & 1) == 0)
      *writePtr++ = *readPtr;

    ++readPtr;
  }

  // Null-terminate the modified string
  *writePtr = 0;
}