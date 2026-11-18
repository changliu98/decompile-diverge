int __cdecl int_range_lookup(unsigned int n_ranges, const ProtobufCIntRange *ranges, int value)
{
  unsigned int start_orig_index; // [rsp+4h] [rbp-28h]
  unsigned int mid; // [rsp+Ch] [rbp-20h]
  unsigned int start; // [rsp+10h] [rbp-1Ch]
  unsigned int n; // [rsp+14h] [rbp-18h]

  if ( !n_ranges )
    return -1;
  start = 0;
  n = n_ranges;
  while ( n > 1 )
  {
    mid = (n >> 1) + start;
    if ( value >= ranges[mid].start_value )
    {
      if ( value < (signed int)(ranges[mid + 1].orig_index - ranges[mid].orig_index + ranges[mid].start_value) )
        return ranges[mid].orig_index + value - ranges[mid].start_value;
      n -= (n >> 1) + 1;
      start = mid + 1;
    }
    else
    {
      n >>= 1;
    }
  }
  if ( n
    && (start_orig_index = ranges[start].orig_index, ranges[start].start_value <= value)
    && value < (int)(ranges[start + 1].orig_index - start_orig_index + ranges[start].start_value) )
  {
    return start_orig_index + value - ranges[start].start_value;
  }
  else
  {
    return -1;
  }
}