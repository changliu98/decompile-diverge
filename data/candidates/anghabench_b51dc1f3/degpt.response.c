int get_sorting_mode(int char_code)
{
  return ((char_code < 0) || (0x7f < char_code)) ? -1 : sorting_mode_table[char_code];
}