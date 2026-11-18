char *__cdecl trim(char *str, char *trim_chars)
{
  char *endstr;

  if ( !str )
    return 0LL;

  // Find the end of the string (null terminator) and step back one character
  for ( endstr = index(str, 0) - 1; endstr >= str; --endstr )
  {
    // If the current character is not in the set of trim_chars, stop trimming
    if ( !index(trim_chars, *endstr) )
      break;

    // Otherwise, truncate the string by replacing the character with a null terminator
    *endstr = 0;
  }

  return str;
}