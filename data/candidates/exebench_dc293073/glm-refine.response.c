char *__cdecl Q_strupr(char *str)
{
  char *cp;

  // Iterate through the string until the null terminator is reached
  for (cp = str; *cp; ++cp)
  {
    // Check if the character is a lowercase ASCII letter ('a' - 'z')
    if (islower(*cp))
    {
      // Convert to uppercase by subtracting the ASCII difference ('a' - 'A' = 32)
      *cp = toupper(*cp);
    }
  }
  
  // Return the original pointer, as is standard for strupr
  return str;
}