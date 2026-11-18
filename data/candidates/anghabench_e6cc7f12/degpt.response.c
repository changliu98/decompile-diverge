// Aligns the input value 'val' up to the nearest multiple of 64.
// Adds 0x3f (63) to handle rounding up, then shifts right by 6 bits (divides by 64),
// and finally shifts left by 6 bits (multiplies by 64) to get the aligned result.
int aligned(int input_value)
{
  return (input_value + 0x3f >> 6) << 6;
}