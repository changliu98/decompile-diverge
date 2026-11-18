void coap_option_nibble(uint32_t option_value, uint8_t *encoded_nibble)
{
  // If value is less than 13, it fits in the 4-bit field directly
  if (option_value < 0xd) {
    *encoded_nibble = (uint8_t)option_value;
  }
  // If value is less than 269 (0x10d), it requires a 1-byte delta with opcode 13 ('\r')
  else if (option_value < 0x10d) {
    *encoded_nibble = '\r';
  }
  // If value is less than 65773 (0x1010d), it requires a 2-byte delta with opcode 14 ('\x0e')
  else if (option_value < 0x1010d) {
    *encoded_nibble = '\x0e';
  }
}