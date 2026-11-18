static int int_range_lookup(unsigned n, const range_t *ranges, int value) {
  unsigned low, mid, high;
  if (n == 0) return -1;
  low = 0;
  high = n;
  while (high > 1) {
    mid = low + (high >> 1);
    if (value < ranges[mid].low) {
      high >>= 1;
    } else if (value >= ranges[mid + 1].high - ranges[mid].high +
                            ranges[mid].low) {
      high -= (mid + 1);
      low = mid + 1;
    } else {
      return ranges[mid].high + value - ranges[mid].low;
    }
  }
  if (high == 0 || value < ranges[low].low ||
      value >= ranges[low + 1].high - ranges[low].high + ranges[low].low)
    return -1;
  return ranges[low].high + value - ranges[low].low;
}