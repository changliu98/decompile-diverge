int func0(int *values, int length)
{
  int index;
  int weighted_total = 0;
  
  // Iterate through the array from index 0 to l-1
  for (index = 0; index < length; index = index + 1) {
    // Calculate weighted sum: each element arr[i] is multiplied by a weight
    // derived from its position (i+1) and remaining length (l-i), plus 1, divided by 2
    weighted_total = (((index + 1) * (length - index) + 1) / 2) * values[index] + weighted_total;
  }
  return weighted_total;
}