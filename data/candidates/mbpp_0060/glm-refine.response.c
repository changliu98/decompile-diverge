// Computes the length of the longest subsequence of `arr` such that
// every pair of consecutive chosen elements differs by at most 1.
//
// This is a classic O(n^2) DP:
//   mls[i] = length of the longest valid subsequence ending at index i
//
// arr: input array of integers
// n:   number of elements in arr
// returns: length of the longest valid subsequence (0 if n == 0)
int __cdecl longest_subseq_adj_diff_le_one(int *arr, int n)
{
  int k;          // [rsp+4h]  [rbp-2Ch]  index for the final max-scan loop
  int j;          // [rsp+8h]  [rbp-28h]  inner-loop index (candidate predecessor)
  int i;          // [rsp+Ch]  [rbp-24h]  outer-loop index (current DP position)
  int init_i;     // [rsp+10h] [rbp-20h]  index for the initialization loop
  int max_len;    // [rsp+14h] [rbp-1Ch]  running maximum of mls[]
  int *mls;       // [rsp+18h] [rbp-18h]  DP table: mls[i] = best length ending at i

  // Allocate DP table (one int per element).
  mls = (int *)malloc(4LL * n);
  max_len = 0;

  // Base case: a single element alone is always a valid subsequence of length 1.
  for ( init_i = 0; init_i < n; ++init_i )
    mls[init_i] = 1;

  // DP transition: try to extend a subsequence ending at j with arr[i].
  // The extension is valid only if |arr[i] - arr[j]| <= 1, and we only
  // update when doing so strictly improves mls[i].
  for ( i = 0; i < n; ++i )
  {
    for ( j = 0; j < i; ++j )
    {
      if ( abs(arr[i] - arr[j]) <= 1 && mls[i] < mls[j] + 1 )
        mls[i] = mls[j] + 1;
    }
  }

  // The answer is the maximum value in the DP table.
  for ( k = 0; k < n; ++k )
  {
    if ( max_len < mls[k] )
      max_len = mls[k];
  }

  free(mls);
  return max_len;
}