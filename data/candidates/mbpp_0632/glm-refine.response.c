void __cdecl func0(int *num_list, int size, int *result)
{
  int non_zero_idx = 0;
  int zero_count = 0;

  // First pass: copy all non-zero elements to the front of 'result'
  for (int i = 0; i < size; ++i)
  {
    if (num_list[i] != 0)
    {
      result[non_zero_idx++] = num_list[i];
    }
    else
    {
      ++zero_count;
    }
  }

  // Second pass: pad the remaining slots in 'result' with zeros
  for (int i = 0; i < zero_count; ++i)
  {
    result[non_zero_idx++] = 0;
  }
}