uint16_t __cdecl get_bits(heatshrink_decoder *hsd, uint8_t count)
{
  uint16_t input_index; // cx
  int i; // [rsp+0h] [rbp-18h]
  uint16_t accumulator; // [rsp+4h] [rbp-14h]

  accumulator = 0;
  if ( count > 0xFu )
    return -1;
  if ( !hsd->input_size && hsd->bit_index < 1 << (count - 1) )
    return -1;
  for ( i = 0; i < count; ++i )
  {
    if ( !hsd->bit_index )
    {
      if ( !hsd->input_size )
        return -1;
      input_index = hsd->input_index;
      hsd->input_index = input_index + 1;
      hsd->current_byte = hsd->buffers[input_index];
      if ( hsd->input_index == hsd->input_size )
      {
        hsd->input_index = 0;
        hsd->input_size = 0;
      }
      hsd->bit_index = 0x80;
    }
    accumulator *= 2;
    if ( (hsd->bit_index & hsd->current_byte) != 0 )
      accumulator |= 1u;
    hsd->bit_index = (int)hsd->bit_index >> 1;
  }
  return accumulator;
}