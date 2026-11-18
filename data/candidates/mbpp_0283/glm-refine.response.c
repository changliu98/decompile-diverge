// This function checks if a number is a "self-describing number" (or autobiographical number).
// A self-describing number is an integer `n` where the digit at position `i` (0-indexed from right to left)
// indicates the total number of times the digit `i` appears in the number itself.
// Note: The original loop limits the check to the first 10 digits (0 through 9).
bool __cdecl is_self_describing_number(int n)
{
  int digit_count; // Tracks the occurrences of the current digit `i`
  int temp;        // Temporary variable to extract digits from `n`
  int i;           // The digit currently being evaluated (0-9)

  for ( i = 0; i < 10; ++i )
  {
    temp = n;
    digit_count = 0;
    
    // Count how many times the digit `i` appears in `n`
    while ( temp > 0 )
    {
      if ( temp % 10 == i )
        ++digit_count;
        
      // Early exit: if the count of digit `i` exceeds `i`, the condition is violated
      if ( digit_count > i )
        return false;
        
      temp /= 10;
    }
  }
  
  // If all digit counts are less than or equal to their respective values `i`, return true
  return true;
}