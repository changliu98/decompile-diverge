float binary_search(float x, float *table, int size)
{
 int i, low, high;
 float f;
 if (x == table[0])
  return 0.0;
 else if (x < table[0])
  return -1.0;
 else if (x > table[size-1])
  return -1.0;
 else if (x == table[size-1])
  return size-1;
 else {
  low = 0;
  high = size-1;
  while (low <= high) {
   i = (low + high) / 2;
   if (x < table[i]) {
    high = i - 1;
   }
   else if (x > table[i]) {
    low = i + 1;
   }
   else {
    return i;
   }
  }

  f = (x - table[high]) / (table[low] - table[high]);
  return (float)high * (1.0 - f) + (float)low * f;
 }
}