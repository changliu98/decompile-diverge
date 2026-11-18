void __cdecl func0(int *num_list, int n, int *output)
{
  int i;
  int output_index = 0;
  int first_element = num_list[0];
  int count_first = 0;

  // Count the occurrences of the first element in the array
  for (i = 0; i < n; ++i)
  {
    if (num_list[i] == first_element)
      ++count_first;
  }

  // Move all elements that are not the first element to the output array
  for (i = 0; i < n; ++i)
  {
    if (num_list[i] != first_element)
    {
      output[output_index++] = num_list[i];
    }
  }

  // Append all occurrences of the first element to the end of the output array
  for (i = 0; i < count_first; ++i)
  {
    output[output_index++] = first_element;
  }
}