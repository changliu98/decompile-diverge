void __cdecl snake_upcase_char(char *c)
{
  // Check if the character is a lowercase letter ('a' to 'z')
  if (*c >= 'a' && *c <= 'z')
  {
    // Convert to uppercase. 
    // (This is equivalent to the original bitwise operation: *c &= ~0x20u;)
    *c = toupper(*c); 
  }
  else if (*c == '-')
  {
    // Replace hyphens with underscores
    *c = '_';
  }
}