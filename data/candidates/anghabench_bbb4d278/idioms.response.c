void coap_option_nibble(unsigned int value, unsigned char *nibble)
{
  if (value < 13)
    *nibble = value;
  else if (value <= 268)
    *nibble = 13;
  else if (value <= 65516)
    *nibble = 14;
}