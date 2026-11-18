static state_t st_step_search(state_t_data *sdata) {
  unsigned short input_buffer_size = get_input_buffer_size(sdata);
  unsigned short lookahead_size = get_lookahead_size(sdata);
  unsigned short offset = sdata->offset;
  unsigned short end;
  unsigned short start;
  unsigned short max_length;
  unsigned short length;
  unsigned short distance;
  unsigned short i;
  unsigned short j;
  unsigned short lookahead_size_to_use;
  lookahead_size_to_use = is_finishing(sdata) ? 1 : lookahead_size;
  if (offset > sdata->input_size - lookahead_size_to_use) {
    return ST_STEP_FINISH;
  }
  i = get_input_offset(sdata);
  end = offset + i;
  start = end - input_buffer_size;
  max_length = lookahead_size;
  if (max_length > sdata->input_size - offset) {
    max_length = sdata->input_size - offset;
  }
  length = 0;
  distance = find_longest_match(sdata, start, end, max_length, &length);
  if (distance == 0xFFFF) {
    sdata->offset++;
    sdata->length = 0;
  } else {
    sdata->distance = distance;
    sdata->length = length;
  }
  return 3;
}