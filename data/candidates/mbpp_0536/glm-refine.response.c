void __cdecl func0(int *input_list, int list_size, int step, int *output_list, int *output_size)
{
  int out_idx = 0;
  
  // Iterate through the input list with a given step size
  for (int i = 0; i < list_size; i += step)
  {
    output_list[out_idx++] = input_list[i];
  }
  
  *output_size = out_idx;
}