void func0(int *input_array, int n, int *output_array)
{
  // Iterate through each element of the input array
  for (int index = 0; index < n; index++) {
    // Perform bitwise NOT operation on test_tup[i] and store the result in res[i]
    // Equivalent to res[i] = ~test_tup[i]
    output_array[index] = input_array[index] ^ 0xffffffff;
  }
}