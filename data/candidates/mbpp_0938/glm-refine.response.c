void __cdecl func0(int *A, int *B, int *C, int p, int q, int r, int *res)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int min_diff = 0x7FFFFFFF;
  int best_i = 0;
  int best_j = 0;
  int best_k = 0;

  // Iterate as long as all three arrays have elements remaining
  while ( i < p && j < q && k < r )
  {
    int a = A[i];
    int b = B[j];
    int c = C[k];

    // Find the minimum and maximum values among the current elements
    int min_val = a < b ? (a < c ? a : c) : (b < c ? b : c);
    int max_val = a > b ? (a > c ? a : c) : (b > c ? b : c);

    int diff = max_val - min_val;

    // Update the best result if a smaller difference is found
    if ( diff < min_diff )
    {
      best_i = i;
      best_j = j;
      best_k = k;
      min_diff = diff;
    }

    // Early exit if the absolute minimum difference is found
    if ( !min_diff )
      break;

    // Advance the pointer pointing to the minimum element
    if ( a == min_val )
      ++i;
    else if ( b == min_val )
      ++j;
    else
      ++k;
  }

  // Store the closest triplet into the result array
  res[0] = A[best_i];
  res[1] = B[best_j];
  res[2] = C[best_k];
}