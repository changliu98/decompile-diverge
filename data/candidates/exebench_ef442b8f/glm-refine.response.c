Converts all lowercase ASCII characters in a string to uppercase
void __cdecl toUpperCase(char *str)
{
  // Iterate through the string until the null terminator is reached
  while ( *str )
  {
    // Check if the current character is a lowercase ASCII letter ('a' to 'z')
    if ( *str >= 'a' && *str <= 'z' )
    {
      // Convert to uppercase by subtracting the ASCII difference (32)
      *str -= 'a' - 'A'; 
    }
    ++str;
  }
}