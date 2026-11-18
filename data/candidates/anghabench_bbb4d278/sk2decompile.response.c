void coap_option_nibble(unsigned int delta, unsigned char *nibble) {
  if (delta < 13) {
    *nibble = delta;
  } else if (delta < 269) {
    *nibble = 13;
  } else if (delta < 65805) {
    *nibble = 14;
  }
}