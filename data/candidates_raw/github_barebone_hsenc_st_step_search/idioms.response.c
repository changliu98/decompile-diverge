static enum HSE_state hse_find_match(struct heatshrink_encoder *hse)
{
  struct heatshrink_encoder *hse_ = hse;
  unsigned short window_length = hse->window_length;
  unsigned short lookahead_sz = hse->lookahead_sz;
  unsigned short match_scan_index = hse->match_scan_index;
  unsigned short input_size = hse->input_size;
  unsigned short input_offset = hse->input_offset;
  unsigned short input_end = match_scan_index + input_offset;
  unsigned short input_start = input_end - window_length;
  unsigned short max_possible = lookahead_sz;
  if (input_end > input_size)
  {
    if (hse->fin)
      return HSES_FIN;
    return HSES_SAVE_BACKLOG;
  }
  input_offset = hse->input_offset;
  input_end = match_scan_index + input_offset;
  input_start = input_end - window_length;
  max_possible = lookahead_sz;
  if (input_size - match_scan_index < lookahead_sz)
    max_possible = input_size - match_scan_index;
  unsigned short match_length = 0;
  unsigned short match_pos = hse_find_match_pos(hse_, input_start, input_end, max_possible, &match_length);
  if (match_pos == (unsigned short)-1)
  {
    hse_->match_scan_index++;
    hse_->match_length = 0;
  }
  else
  {
    hse->match_pos = match_pos;
    hse->match_length = match_length;
  }
  return HSES_FIND_MATCH;
}