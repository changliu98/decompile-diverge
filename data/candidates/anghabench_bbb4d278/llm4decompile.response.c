void
coap_option_nibble(uint32_t value, uint8_t *nibble)
{
  if (value <= 12) {
    *nibble = (uint8_t)value;
  } else if (value <= 268) {
    *nibble = 13;
  } else if (value <= 65796) {
    *nibble = 14;
  }
}