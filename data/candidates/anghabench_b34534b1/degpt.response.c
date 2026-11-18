/*
 * _getbase - Determine the numeric base from a string prefix.
 *
 * This function checks the first two characters of the string 'p' to determine
 * the base of the number representation. It supports the following prefixes:
 *   - "0n" or "0t" : Decimal (base 10)
 *   - "0o"         : Octal (base 8)
 *   - "0x"         : Hexadecimal (base 16)
 *
 * If no recognized prefix is found, or if the string does not start with '0',
 * the base defaults to 10 (decimal).
 *
 * Parameters:
 *   p       : Pointer to the string to analyze.
 *   basep   : Pointer to an integer where the determined base will be stored.
 *
 * Returns:
 *   A pointer to the character immediately following the base prefix, or to
 *   the original string if no prefix was recognized.
 */
char * _getbase(char *str, int *base)
{
  /* Check if the string starts with '0' */
  if (*str == '0') {
    /* Examine the second character to determine the specific base */
    switch(str[1]) {
    case 'n':
    case 't':
      /* "0n" or "0t" indicates decimal */
      *base = 10;
      /* Return pointer to the character after the prefix */
      return str + 2;
    case 'o':
      /* "0o" indicates octal */
      *base = 8;
      /* Return pointer to the character after the prefix */
      return str + 2;
    case 'x':
      /* "0x" indicates hexadecimal */
      *base = 0x10;
      /* Return pointer to the character after the prefix */
      return str + 2;
    default:
      /* No recognized prefix; default to decimal */
      *base = 10;
      /* Return the original pointer as no prefix was consumed */
      return str;
    }
  }
  else {
    /* String does not start with '0'; default to decimal */
    *base = 10;
    /* Return the original pointer */
    return str;
  }
}