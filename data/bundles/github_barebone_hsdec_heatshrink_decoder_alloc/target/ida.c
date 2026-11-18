heatshrink_decoder *__cdecl heatshrink_decoder_alloc(
        uint16_t input_buffer_size,
        uint8_t window_sz2,
        uint8_t lookahead_sz2)
{
  heatshrink_decoder *hsd; // [rsp+8h] [rbp-28h]

  if ( window_sz2 < 4u
    || window_sz2 > 0xFu
    || !input_buffer_size
    || lookahead_sz2 < 3u
    || lookahead_sz2 >= (int)window_sz2 )
  {
    return 0LL;
  }
  hsd = (heatshrink_decoder *)malloc(input_buffer_size + (1 << window_sz2) + 18LL);
  if ( !hsd )
    return 0LL;
  hsd->input_buffer_size = input_buffer_size;
  hsd->window_sz2 = window_sz2;
  hsd->lookahead_sz2 = lookahead_sz2;
  heatshrink_decoder_reset(hsd);
  return hsd;
}