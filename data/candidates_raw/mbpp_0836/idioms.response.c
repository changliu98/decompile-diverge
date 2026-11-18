int max_subarray(int *array, int size){
  int max_so_far = (-0x7fffffff - 1);
  int max_ending_here = 0;
  int start = 0; int end = 0;
  int i = 0;
  for (i = 0; i < size; i++) {
    max_ending_here = max_ending_here + array[i];
    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
      end = i;
    }
    if (max_ending_here < 0) {
      max_ending_here = 0;
      start = i + 1;
    }
  }
  return (end - start + 1);
}