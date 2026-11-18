bool __cdecl func0(__int64 x)
{
  __int64 shifted_val; // xa
  __int64 shift_count; // p

  // Return false if x is even
  if ((x & 1) == 0)
    return false;
    
  // Fast path / explicit check for x = 1 (where p = 1)
  if (x == 1)
    return true;

  shifted_val = x + 1;
  shift_count = 0;
  
  // Strip factors of 2 from (x + 1)
  while ((shifted_val & 1) == 0)
  {
    shifted_val >>= 1;
    
    // If the number of shifts equals the remaining value, 
    // then x + 1 == shift_count * 2^shift_count
    if (++shift_count == shifted_val)
      return true;
  }
  
  return false;
}