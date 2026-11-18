void coap_option_nibble(uint32_t value,uint8_t *nibble)

{
  uint8_t *nibble_local;
  uint32_t value_local;
  
  if (value < 0xd) {
    *nibble = (uint8_t)value;
  }
  else if (value < 0x10d) {
    *nibble = '\r';
  }
  else if (value < 0x1010d) {
    *nibble = '\x0e';
  }
  return;
}