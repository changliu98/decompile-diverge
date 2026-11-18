int protobuf_CIntRange_to_orig_index(unsigned int n_ranges, struct ProtobufCIntRange *ranges, int value) {
  if (n_ranges == 0) {
    return -1;
  }
  unsigned int start = 0;
  unsigned int n = n_ranges;
  while (n > 1) {
    unsigned int mid = start + (n >> 1);
    if (value < ranges[mid].start_value) {
      n >>= 1;
    } else {
      if (value < ranges[mid + 1].start_value
          + (ranges[mid + 1].orig_index - ranges[mid].orig_index)) {
        int index = ranges[mid].orig_index
          + (value - ranges[mid].start_value);
        return index;
      }
      n = (n >> 1) + 1;
      start = mid + 1;
    }
  }
  if (n == 0) {
    return -1;
  }
  unsigned int start_orig_index = ranges[start].orig_index;
  if (value < ranges[start].start_value
      || value >= ranges[start + 1].start_value
      + (ranges[start + 1].orig_index - ranges[start].orig_index)) {
    return -1;
  }
  int index = start_orig_index + (value - ranges[start].start_value);
  return index;
}