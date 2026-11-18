int __cdecl cal_intervals(int *stalls, int *intervals, int num)
{
  int i = 0;
  int segs = 0;
  int inter;

  // Skip leading zeros
  while (i < num && stalls[i] == 0)
    ++i;

  while (i < num)
  {
    // Skip non-zero values
    while (i < num && stalls[i] != 0)
      ++i;

    // Count contiguous zeros
    for (inter = 0; i < num && stalls[i] == 0; ++inter)
      ++i;

    // Record the length of the zero interval if we haven't reached the end
    if (i < num)
      intervals[segs++] = inter;
  }

  // Total intervals is the number of recorded segments plus 1
  return segs + 1;
}