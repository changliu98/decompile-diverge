char *__cdecl func0(int *test_tup, int size)
{
  int res = 0;

  // Iterate over the elements of the tuple
  for (int i = 0; i < size; ++i)
  {
    // Treat the tuple elements as binary digits (bits) to form an integer
    // Element at index 0 is the Most Significant Bit (MSB)
    double bit_val = (double)test_tup[i];
    res = (int)(bit_val * pow(2.0, (double)(size - 1 - i)) + (double)res);
  }

  // Allocate a 12-byte buffer to hold the resulting string (max 10 digits + sign + null)
  char *result_str = (char *)malloc(12);
  sprintf(result_str, "%d", (unsigned int)res);
  
  return result_str;
}