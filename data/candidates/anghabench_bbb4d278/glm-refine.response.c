void __cdecl coap_option_nibble(uint32_t value, uint8_t *nibble)
{
  if (value <= 0xC)
  {
    *nibble = value;
  }
  else if (value <= 0x10C)
  {
    *nibble = 13;
  }
  else if (value <= 0x1010C)
  {
    *nibble = 14;
  }
  // If value > 0x1010C, the function leaves *nibble unmodified
}