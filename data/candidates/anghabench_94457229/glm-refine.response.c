uint32_t __cdecl clk_div_even_up(uint32_t divisor)
{
  // A divisor of 1 is already even, no calculation needed
  if (divisor == 1)
    return 1;

  // Round up to the nearest even number
  // (Equivalent to: (divisor + 1) & 0xFFFFFFFE)
  return divisor + (divisor % 2);
}