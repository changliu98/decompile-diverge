// Optimized for reverse engineering readability
void __cdecl square_array(int *input_array, int *output_array, int array_size)
{
  int index; // [rsp+0h] [rbp-18h]

  for ( index = 0; index < array_size; ++index )
    output_array[index] = input_array[index] * input_array[index];
}