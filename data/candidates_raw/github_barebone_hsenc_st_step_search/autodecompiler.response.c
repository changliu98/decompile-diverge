int st_step_search(struct lzss *lzss)
{
 int len, min_match, lookahead_sz, input_size, fin;
 unsigned short offset, start, end, max_match, match_length, match_pos;

 input_size = get_input_buffer_size(lzss);
 lookahead_sz = get_lookahead_size(lzss);
 min_match = lzss->min_match;
 fin = !!is_finishing(lzss) & 1;
 if (min_match > input_size - (fin ? 1 : lookahead_sz)) {
  len = (fin ? 8 : 7);
 } else {
  offset = get_input_offset(lzss);
  end = lzss->buffer_end + min_match;
  start = end - input_size;
  max_match = lookahead_sz;
  if (lzss->buffer_end - min_match < lookahead_sz)
   max_match = lzss->buffer_end - min_match;
  match_length = 0;
  match_pos = find_longest_match(lzss, start, end, max_match,
     &match_length);
  if (match_pos == 0xffff) {
   lzss->literal_count++;
   lzss->literal_length = 0;
   len = 3;
  } else {
   lzss->match_position = match_pos;
   lzss->match_length = match_length;
   len = 3;
  }
 }

 return len;
}