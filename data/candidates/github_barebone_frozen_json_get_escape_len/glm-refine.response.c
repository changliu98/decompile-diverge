int __cdecl json_get_escape_len(const char *s, int len)
{
  switch (*s)
  {
    case '"':
    case '/':
    case '\\':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
      // Simple escape characters (e.g., \", \n, \t) take exactly 2 characters.
      // If the remaining length is less than 2, it's an incomplete sequence.
      return (len < 2) ? -2 : 1;

    case 'u':
      // Unicode escape sequences (e.g., \uXXXX) require exactly 6 characters.
      if (len < 6)
        return -2;
      
      // Validate that the 4 characters following '\u' are hexadecimal digits.
      if (json_isxdigit(s[1]) && 
          json_isxdigit(s[2]) && 
          json_isxdigit(s[3]) && 
          json_isxdigit(s[4]))
      {
        return 5;
      }
      return -1;

    default:
      // Invalid escape character.
      return -1;
  }
}