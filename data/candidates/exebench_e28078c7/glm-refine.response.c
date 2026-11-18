Optimized and annotated for reverse engineering
bool __cdecl parse_int(const char *str, int *num)
{
  int multiplier;       // [rsp+2h] [rbp-2Ch]
  int length;           // [rsp+6h] [rbp-28h]
  int digit;            // [rsp+Ah] [rbp-24h]
  bool is_negative;     // [rsp+Eh] [rbp-20h]
  int i;                // [rsp+12h] [rbp-1Ch]

  multiplier = 1;
  *num = 0;
  
  // Check for '-' (ASCII 45) and set the starting index accordingly
  is_negative = (*str == '-');
  i = is_negative;

  // Calculate the magnitude multiplier (10^(len-1)) for the upcoming digits
  for (length = 1; str[length]; ++length)
    multiplier *= 10;

  // Parse each digit from the starting index to the end of the string
  while (str[i])
  {
    digit = str[i] - '0'; // Convert char to int (ASCII '0' is 48)
    
    // If the character is not a valid digit, fail and return 0 (false)
    if (digit < 0 || digit > 9)
      return false;
      
    // Decrease the multiplier for the next positional digit
    // (Skipped for the very first character to avoid premature division)
    if (i > 0)
      multiplier /= 10;
      
    *num += digit * multiplier;
    ++i;
  }

  // Apply the sign if a minus sign was encountered
  if (is_negative)
    *num = -*num;
    
  return true; // Return 1 (true) on success
}