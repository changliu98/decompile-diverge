uint32_t clk_div_even_up(uint32_t input_value)
{
  // If the input is 1, return 1 to avoid changing it
  if (input_value == 1) {
    return 1;
  }
  // Round up to the next even number by adding 1 and clearing the least significant bit
  return input_value + 1 & 0xfffffffe;
}