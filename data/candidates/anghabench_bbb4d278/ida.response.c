void __cdecl coap_option_nibble(uint32_t value, uint8_t *nibble)
{
  if ( value >= 0xD )
  {
    if ( value > 0x10C )
    {
      if ( value <= 0x1010C )
        *nibble = 14;
    }
    else
    {
      *nibble = 13;
    }
  }
  else
  {
    *nibble = value;
  }
}