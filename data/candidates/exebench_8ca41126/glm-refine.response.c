char __cdecl zhalfstr(char *s)
{
  int back = 0;          // Tracks how many leading zeros to skip (shift back)
  int nonzero = 0;       // Boolean flag: have we encountered a non-zero character yet?
  int index = -1;        // Current index in the original string
  char lastchar = '0';   // The last character processed from the original string
  char curchar = '0';    // The current character being processed
  char nextchar;         // The next character to be processed

  // Iterate until the null terminator is reached and processed
  while (curchar)
  {
    nextchar = s[index + 1];

    // Core mathematical operation:
    // 1. (nextchar - '0') >> 1: Integer division of the next digit by 2.
    // 2. 5 * LSB(curchar): Adds 5 if the current digit is odd (equivalent to adding 10/2).
    // 3. + '0': Converts the resulting mathematical half back to an ASCII character.
    // This effectively computes: (curchar_digit + 10 * nextchar_digit) / 2
    char half_digit = 5 * LSB(curchar) + '0' + ((nextchar - '0') >> 1);
    
    // Write the computed character back into the string.
    // The 'back' offset compacts the string by removing leading zeros.
    s[index - back + 1] = half_digit;

    // Update the leading zero tracking
    if (half_digit != '0' || nonzero)
    {
      nonzero = 1;
    }
    else
    {
      ++back;
    }

    // Advance to the next character
    lastchar = curchar;
    curchar = nextchar;
    ++index;
  }

  // Finalize the resulting string
  if (index == back)
  {
    // If the entire string consisted of leading zeros, default it to "0"
    *s = '0';
    s[1] = '\0';
  }
  else
  {
    // Otherwise, null-terminate the compacted string
    s[index - back] = '\0';
  }

  // Returns the last non-null character processed from the original string
  return lastchar;
}