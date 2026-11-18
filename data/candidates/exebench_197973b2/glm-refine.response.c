void __cdecl computesizes(int *nums, int ntotal, int *narray, int *nhash)
{
  int n;
  int na;
  int a;
  int i;

  a = *nums;
  na = *nums;
  n = (*nums == 0) ? -1 : 0;

  for ( i = 1; ; ++i )
  {
    // Break if the current array size is large enough 
    // (i.e., *narray >= 2^(i-1) and a < *narray)
    if ( !(a < *narray && *narray >= (1 << (i - 1))) )
      break;

    if ( nums[i] > 0 )
    {
      a += nums[i];
      if ( a >= (1 << (i - 1)) )
      {
        n = i;
        na = a;
      }
    }
  }

  *nhash = ntotal - na;
  *narray = (n == -1) ? 0 : (1 << n);
}