int func0(int *a,int size)

{
  int i;
  int s;
  int end;
  int start;
  int max_ending_here;
  int max_so_far;
  int size_local;
  int *a_local;
  
  max_so_far = -0x80000000;
  max_ending_here = 0;
  start = 0;
  end = 0;
  s = 0;
  for (i = 0; i < size; i = i + 1) {
    max_ending_here = a[i] + max_ending_here;
    if (max_so_far < max_ending_here) {
      start = s;
      end = i;
      max_so_far = max_ending_here;
    }
    if (max_ending_here < 0) {
      max_ending_here = 0;
      s = i + 1;
    }
  }
  return (end - start) + 1;
}