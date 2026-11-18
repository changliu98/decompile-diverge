void __cdecl reverse(char *s)
{
  char *start;
  char *end;
  char temp;

  if ( !s )
    return;

  start = s;
  end = s;

  // Find the null terminator to determine the end of the string
  while ( *end )
    ++end;

  // Set 'end' to the last valid character before the null terminator
  --end;

  // Swap characters from the outside in
  while ( start < end )
  {
    temp = *end;
    *end-- = *start;
    *start++ = temp;
  }
}