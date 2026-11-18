HSE_state __cdecl st_step_search(heatshrink_encoder *hse)
{
  int v1; // eax
  HSE_state v2; // eax
  int v4; // [rsp+0h] [rbp-30h]
  uint16_t match_pos; // [rsp+Ch] [rbp-24h]
  uint16_t match_length; // [rsp+Eh] [rbp-22h] BYREF
  uint16_t max_possible; // [rsp+10h] [rbp-20h]
  uint16_t start; // [rsp+12h] [rbp-1Eh]
  uint16_t end; // [rsp+14h] [rbp-1Ch]
  uint16_t input_offset; // [rsp+16h] [rbp-1Ah]
  bool fin; // [rsp+19h] [rbp-17h]
  uint16_t msi; // [rsp+1Ah] [rbp-16h]
  uint16_t lookahead_sz; // [rsp+1Ch] [rbp-14h]
  uint16_t window_length; // [rsp+1Eh] [rbp-12h]
  heatshrink_encoder *hsea; // [rsp+20h] [rbp-10h]

  hsea = hse;
  window_length = get_input_buffer_size(hse);
  lookahead_sz = get_lookahead_size(hse);
  msi = hse->match_scan_index;
  v1 = is_finishing(hse);
  fin = v1 != 0;
  if ( v1 )
    v4 = 1;
  else
    v4 = lookahead_sz;
  if ( msi <= hse->input_size - v4 )
  {
    input_offset = get_input_offset(hsea);
    end = msi + input_offset;
    start = msi + input_offset - window_length;
    max_possible = lookahead_sz;
    if ( hsea->input_size - msi < lookahead_sz )
      max_possible = hsea->input_size - msi;
    match_length = 0;
    match_pos = find_longest_match(hsea, start, end, max_possible, &match_length);
    if ( match_pos == 0xFFFF )
    {
      ++hsea->match_scan_index;
      hsea->match_length = 0;
    }
    else
    {
      hsea->match_pos = match_pos;
      hsea->match_length = match_length;
    }
    return 3;
  }
  else
  {
    v2 = HSES_SAVE_BACKLOG;
    if ( fin )
      return 8;
    return v2;
  }
}