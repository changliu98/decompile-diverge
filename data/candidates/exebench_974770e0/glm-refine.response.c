char *__cdecl envstring(char *str)
{
  char *s; // [rsp+0h] [rbp-10h]

  // Iterate through the string until the null terminator is reached
  for ( s = str; *s; ++s )
  {
    // Check if the character is a lowercase letter ('a' - 'z')
    if ( *s >= 'a' && *s <= 'z' )
    {
      *s -= 32; // Convert to uppercase
    }
    // Check if the character is a hyphen ('-')
    else if ( *s == '-' )
    {
      *s = '_'; // Replace hyphen with underscore
    }
    // Check if the character is outside the uppercase letter range ('A' - 'Z')
    else if ( *s < 'A' || *s > 'Z' )
    {
      *str = 0; // Terminate string on the first invalid character
      return str;
    }
  }
  return str;
}