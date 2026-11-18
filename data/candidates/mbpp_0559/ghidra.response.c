int func0(int *a,int size)

{
  int i;
  int max_ending_here;
  int max_so_far;
  int size_local;
  int *a_local;
  
  max_so_far = 0;
  max_ending_here = 0;
  for (i = 0; i < size; i = i + 1) {
    max_ending_here = max_ending_here + a[i];
    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
    else if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }
  }
  return max_so_far;
}