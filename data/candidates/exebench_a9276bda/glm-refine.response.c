char *__cdecl intToString(char *buff, unsigned int val)
{
  int i; // String index, starting from the end of the buffer

  // Null-terminate the maximum possible length (9 digits for a 32-bit integer)
  buff[9] = '\0';

  // Iterate backwards from the last possible digit index down to 0
  for ( i = 8; i >= 0; --i )
  {
    // Convert the least significant decimal digit to its ASCII character
    buff[i] = (val % 10) + '0';
    
    // Shift the value down by one decimal digit
    val /= 10;
    
    // Early exit: if the value reaches 0, no more digits need to be processed
    if ( !val )
      break;
  }

  // Return the pointer to the start of the formatted string
  return &buff[i];
}