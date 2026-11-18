void __cdecl tosuper(char *str)
{
  // Iterate through the string until the null terminator is reached
  for (int i = 0; str[i]; ++i)
  {
    // Check if the character is a lowercase ASCII letter ('a' to 'z')
    if (str[i] >= 'a' && str[i] <= 'z')
    {
      // Convert to uppercase by subtracting the ASCII difference (32)
      str[i] -= 32;
    }
  }
}