int *__cdecl func0(const int *numbers, int size, int delimiter, int *out_size)
{
  int out_length;
  int *out;
  int out_idx;
  int in_idx;

  // Calculate the size of the output array.
  // If size > 0, we need space for the original elements plus (size - 1) delimiters.
  if (size <= 0)
    out_length = 0;
  else
    out_length = 2 * size - 1;

  *out_size = out_length;
  out = (int *)malloc(4LL * out_length);

  if (size > 0)
  {
    // Copy the first element
    out[0] = numbers[0];

    // Interleave the remaining elements with the delimiter
    out_idx = 1;
    in_idx = 1;
    while (in_idx < size)
    {
      out[out_idx] = delimiter;
      out[out_idx + 1] = numbers[in_idx];
      
      out_idx += 2;
      in_idx++;
    }
  }

  return out;
}