int int_range_lookup(uint n_ranges,ProtobufCIntRange *ranges,int value)

{
  uint uVar1;
  uint range_size;
  uint start_orig_index;
  uint new_start;
  uint mid;
  uint start;
  uint n;
  int value_local;
  ProtobufCIntRange *ranges_local;
  uint n_ranges_local;
  
  if (n_ranges != 0) {
    start = 0;
    n = n_ranges;
    while (1 < n) {
      uVar1 = start + (n >> 1);
      if (value < ranges[uVar1].start_value) {
        n = uVar1 - start;
      }
      else {
        if (value < (int)(ranges[uVar1].start_value +
                         (ranges[uVar1 + 1].orig_index - ranges[uVar1].orig_index))) {
          return (value - ranges[uVar1].start_value) + ranges[uVar1].orig_index;
        }
        n = (start + n) - (uVar1 + 1);
        start = uVar1 + 1;
      }
    }
    if (n != 0) {
      if ((ranges[start].start_value <= value) &&
         (value < (int)(ranges[start].start_value +
                       (ranges[start + 1].orig_index - ranges[start].orig_index)))) {
        return (value - ranges[start].start_value) + ranges[start].orig_index;
      }
    }
  }
  return -1;
}