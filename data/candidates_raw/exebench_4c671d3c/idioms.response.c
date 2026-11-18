void get_min_max_step(int n, long *min1, long *max1, long *step1, long *min2, long *max2, long *step2)
{
  long i;
  for (i = 0; i < 3; i++) {
    if (i < n) {
      min1[i] = min2[i];
      max1[i] = max2[i];
      step1[i] = step2[i];
    }
    else {
      min1[i] = 0;
      max1[i] = 1;
      step1[i] = 1;
    }
  }
}