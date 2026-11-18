heatshrink_decoder *
heatshrink_decoder_alloc(uint16_t input_buffer_size,uint8_t window_sz2,uint8_t lookahead_sz2)

{
  heatshrink_decoder *hsd;
  size_t sz;
  size_t buffers_sz;
  uint8_t lookahead_sz2_local;
  uint8_t window_sz2_local;
  uint16_t input_buffer_size_local;
  heatshrink_decoder *local_10;
  
  if ((((window_sz2 < 4) || (0xf < window_sz2)) || (input_buffer_size == 0)) ||
     ((lookahead_sz2 < 3 || (window_sz2 <= lookahead_sz2)))) {
    local_10 = (heatshrink_decoder *)0x0;
  }
  else {
    local_10 = malloc((long)(int)((1 << (window_sz2 & 0x1f)) + (uint)input_buffer_size) + 0x12);
    if (local_10 == (heatshrink_decoder *)0x0) {
      local_10 = (heatshrink_decoder *)0x0;
    }
    else {
      local_10->input_buffer_size = input_buffer_size;
      local_10->window_sz2 = window_sz2;
      local_10->lookahead_sz2 = lookahead_sz2;
      heatshrink_decoder_reset(local_10);
    }
  }
  return local_10;
}