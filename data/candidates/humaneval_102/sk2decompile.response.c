int _get_next_even_number(int start, int end) {
  if (end < start) {
    return -1;
  }
  if (end == start && end % 2 == 1) {
    return -1;
  }
  if (end % 2 == 1) {
    return end - 1;
  }
  return end;
}