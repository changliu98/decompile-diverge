int find_lcm_of_array(int *array, int size)
{
  int lcm = find_lcm (array[0], array[1]);
  int i = 2;
  for (i = 2; i < size; i++)
    lcm = find_lcm (lcm, array[i]);
  return lcm;
}