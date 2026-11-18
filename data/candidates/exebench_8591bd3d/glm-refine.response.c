char *__cdecl read_prefix(
        char *str,
        int *isref,
        int *isarray,
        int *passin,
        int *passout,
        int *nullok,
        int *isretained,
        int *isreturn)
{
  // Initialize flags to their default values
  *isref = 0;
  *passin = 0;
  *passout = 0;
  *nullok = 1;
  *isarray = 0;
  *isretained = 0;
  *isreturn = 0;

  // Parse prefix characters
  while (1)
  {
    switch (*str)
    {
      case '<':
        *isref = 1;
        *passout = 1;
        break;
      case '>':
        *isref = 1;
        *passin = 1;
        break;
      case '&':
        *isref = 1;
        *passin = 1;
        *passout = 1;
        break;
      case '+':
        *nullok = 0;
        break;
      case ':':
        *isref = 1;
        *passout = 1;
        *nullok = 0;
        *isreturn = 1;
        break;
      case '#':
        *isarray = 1;
        break;
      case '!': // 33 in ASCII
        *isretained = 1;
        break;
      default:
        // Return the pointer when a non-prefix character is encountered
        return str;
    }
    ++str;
  }
}