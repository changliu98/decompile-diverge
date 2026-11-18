size_t __cdecl t_add(size_t a, size_t b, int *ok)
{
  bool is_ok = false;

  // Only attempt the addition if the previous state was valid
  if (*ok) {
    size_t max_val = (a > b) ? a : b;
    
    // Check for unsigned integer overflow/underflow
    is_ok = (a + b) >= max_val;
  }

  *ok = is_ok;

  // Return the sum if no overflow occurred, otherwise return 0
  if (is_ok)
    return a + b;
  else
    return 0;
}