// Checks if two integers have opposite signs.
// The original expression (y ^ x) < 0 is a compiler optimization that checks 
// if the Most Significant Bits (sign bits) of the two integers differ.
bool __cdecl have_opposite_signs(int a, int b)
{
  return (a < 0) != (b < 0);
}