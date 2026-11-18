void __cdecl strupr(char *str)
{
  // Iterate until the null terminator is reached
  while (*str != '\0')
  {
    // Check if the current character is a lowercase ASCII letter ('a' to 'z')
    // ASCII 'a' is 97, 'z' is 122
    if (*str >= 'a' && *str <= 'z')
    {
      // Convert to uppercase by subtracting the ASCII difference (32)
      // ASCII 'a' (97) - 32 = 'A' (65)
      *str -= 32; 
    }
    
    // Move to the next character
    str++;
  }
}