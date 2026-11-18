void __cdecl ft_25_lines(const char *s, float *sign, float *val, int *nbr)
{
  // Convert the character to its integer equivalent (e.g., '0' -> 0, '9' -> 9)
  nbr[1] = *s - '0';
  
  // Check if the character was actually a digit
  if ( (unsigned int)nbr[1] <= 9 )
  {
    // If nbr[0] is a flag/state set to 1, shift the decimal place of 'sign'
    if ( *nbr == 1 )
    {
      *sign = *sign / 10.0f;
    }
    
    // Shift 'val' left by one decimal place and add the new digit
    *val = *val * 10.0f + (float)nbr[1];
  }
}