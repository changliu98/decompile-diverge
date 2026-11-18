int func0(int *array, int size){
  int max_so_far = 0;
  int max_ending_here = 0;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    max_ending_here = max_ending_here + array[i];
    if (max_ending_here < 0)
      max_ending_here = 0;
    else if (max_so_far < max_ending_here)
      max_so_far = max_ending_here;
  }
  return max_so_far;
}