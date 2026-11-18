const char *func0(int interval1_start, int interval1_end, int interval2_start, int interval2_end)
{
  // Find the maximum of the two start bounds
  int overlap_start = (interval1_start > interval2_start) ? interval1_start : interval2_start;
  
  // Find the minimum of the two end bounds
  int overlap_end = (interval1_end < interval2_end) ? interval1_end : interval2_end;
  
  // Calculate the length of the overlapping interval
  int length = overlap_end - overlap_start;

  // If the length is less than 2, it cannot be a prime number
  if (length < 2)
    return "NO";

  // Check if the length is a prime number
  for (int i = 2; i * i <= length; ++i)
  {
    if (length % i == 0)
      return "NO";
  }

  return "YES";
}