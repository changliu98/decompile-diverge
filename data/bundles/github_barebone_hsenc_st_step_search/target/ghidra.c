HSE_state st_step_search(heatshrink_encoder *hse)

{
  uint16_t uVar1;
  int iVar2;
  uint local_38;
  uint16_t match_pos;
  uint16_t match_length;
  uint16_t max_possible;
  uint16_t start;
  uint16_t end;
  uint16_t input_offset;
  _Bool fin;
  uint16_t msi;
  uint16_t lookahead_sz;
  uint16_t window_length;
  heatshrink_encoder *hse_local;
  HSE_state local_c;
  
  hse_local = hse;
  window_length = get_input_buffer_size(hse);
  lookahead_sz = get_lookahead_size(hse_local);
  msi = hse_local->match_scan_index;
  iVar2 = is_finishing(hse_local);
  fin = iVar2 != 0;
  if (fin) {
    local_38 = 1;
  }
  else {
    local_38 = (uint)lookahead_sz;
  }
  if ((int)(hse_local->input_size - local_38) < (int)(uint)msi) {
    local_c = HSES_SAVE_BACKLOG;
    if (fin) {
      local_c = HSES_FLUSH_BITS;
    }
  }
  else {
    input_offset = get_input_offset(hse_local);
    end = input_offset + msi;
    start = end - window_length;
    max_possible = lookahead_sz;
    if ((int)((uint)hse_local->input_size - (uint)msi) < (int)(uint)lookahead_sz) {
      max_possible = hse_local->input_size - msi;
    }
    match_length = 0;
    uVar1 = find_longest_match(hse_local,start,end,max_possible,&match_length);
    if (uVar1 == 0xffff) {
      hse_local->match_scan_index = hse_local->match_scan_index + 1;
      hse_local->match_length = 0;
      local_c = HSES_YIELD_TAG_BIT;
    }
    else {
      hse_local->match_pos = uVar1;
      hse_local->match_length = match_length;
      local_c = HSES_YIELD_TAG_BIT;
    }
  }
  return local_c;
}