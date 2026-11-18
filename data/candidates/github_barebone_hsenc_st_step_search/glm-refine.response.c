HSE_state __cdecl st_step_search(heatshrink_encoder *hse)
{
  uint16_t window_length = get_input_buffer_size(hse);
  uint16_t lookahead_sz = get_lookahead_size(hse);
  uint16_t msi = hse->match_scan_index;
  
  bool fin = is_finishing(hse) != 0;
  uint16_t end_offset = fin ? 1 : lookahead_sz;
  
  if (msi <= hse->input_size - end_offset)
  {
    uint16_t input_offset = get_input_offset(hse);
    uint16_t end = msi + input_offset;
    uint16_t start = msi + input_offset - window_length;
    
    uint16_t max_possible = lookahead_sz;
    if (hse->input_size - msi < lookahead_sz)
    {
      max_possible = hse->input_size - msi;
    }
    
    uint16_t match_length = 0;
    uint16_t match_pos = find_longest_match(hse, start, end, max_possible, &match_length);
    
    if (match_pos == HEATSHRINK_ENCODER_FITTED) // 0xFFFF
    {
      ++hse->match_scan_index;
      hse->match_length = 0;
    }
    else
    {
      hse->match_pos = match_pos;
      hse->match_length = match_length;
    }
    return HSES_YIELD_TAG_BIT; // 3
  }
  else
  {
    if (fin)
    {
      return HSES_FLUSH_BIT_BUFFER; // 8
    }
    return HSES_SAVE_BACKLOG;
  }
}