void standardize(int n,long *min1,long *max1,long *step1,long *min2,long *max2,long *step2)

{
  long k;
  long *max2_local;
  long *min2_local;
  long *step1_local;
  long *max1_local;
  long *min1_local;
  int n_local;
  
  for (k = 0; k < 3; k = k + 1) {
    if (k < n) {
      min1[k] = min2[k];
      max1[k] = max2[k];
      step1[k] = step2[k];
    }
    else {
      min1[k] = 0;
      max1[k] = 1;
      step1[k] = 1;
    }
  }
  return;
}