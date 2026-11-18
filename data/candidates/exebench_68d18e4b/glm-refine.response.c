void __cdecl SwitchToChar(char *str, uint8_t data)
{
  // Convert the upper 4 bits (high nibble)
  str[0] = NIBBLE_TO_HEX(data >> 4);
  
  // Convert the lower 4 bits (low nibble)
  str[1] = NIBBLE_TO_HEX(data & 0xF);
}