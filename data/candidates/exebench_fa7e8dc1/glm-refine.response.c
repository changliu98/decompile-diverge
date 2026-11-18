void __cdecl fancySwap(int *first, int *second)
{
  // Step 1: *first becomes the XOR of the two values
  *first ^= *second;
  
  // Step 2: *second becomes the original *first 
  // (since: original_second ^ (original_first ^ original_second) = original_first)
  *second ^= *first;
  
  // Step 3: *first becomes the original *second
  // (since: (original_first ^ original_second) ^ original_first = original_second)
  *first ^= *second;
}