int func0(int *a,int n,int k)

{
  int i;
  int max_ending_here;
  int max_so_far;
  int k_local;
  int n_local;
  int *a_local;
  
  max_so_far = -0x80000000;
  max_ending_here = 0;
  for (i = 0; i < n * k; i = i + 1) {
    max_ending_here = max_ending_here + a[i % n];
    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }
    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
  }
  return max_so_far;
}