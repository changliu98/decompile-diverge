struct heatshrink_decoder *heatshrink_decoder_alloc(unsigned int input_buffer_size, unsigned char window_sz2, unsigned char lookahead_sz2)
{
  struct heatshrink_decoder *hsd;
  if (window_sz2 < 4 || window_sz2 > 15 || !input_buffer_size ||
      lookahead_sz2 < 3 || lookahead_sz2 >= (int)window_sz2)
    return ((void *)0);
  hsd = (struct heatshrink_decoder *)malloc(sizeof(*hsd) +
      input_buffer_size + (1 << window_sz2));
  if (!hsd)
    return ((void *)0);
  hsd->input_buffer_size = input_buffer_size;
  hsd->window_sz2 = window_sz2;
  hsd->lookahead_sz2 = lookahead_sz2;
  heatshrink_decoder_reset(hsd);
  return hsd;
}