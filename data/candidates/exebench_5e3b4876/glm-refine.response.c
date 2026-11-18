unsigned int __cdecl scan_8long(const char *str, unsigned __int64 *out_val)
{
  unsigned __int64 digit;      // Holds the numeric value of the current character
  unsigned __int64 parsed_val; // Accumulator for the final parsed integer
  unsigned int parse_count;    // Number of valid octal characters processed

  parse_count = 0;
  parsed_val = 0LL;
  
  while ( 1 )
  {
    // Convert ASCII character to its integer value.
    // '0' is ASCII 48. Valid octal digits ('0' through '7') will result in 0 through 7.
    // Any other character will result in a value >= 8, breaking the loop.
    digit = (unsigned __int8)(str[parse_count] - '0');
    
    if ( digit >= 8 )
      break;
      
    // Shift the current accumulated value by one octal digit (multiply by 8) 
    // and add the new digit.
    parsed_val = (parsed_val * 8) + digit;
    ++parse_count;
  }
  
  *out_val = parsed_val;
  return parse_count;
}