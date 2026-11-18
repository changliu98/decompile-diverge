int __cdecl sort_omegas(double *v)
{
  double min01, max01, min23, max23;
  int min_idx = 0;

  // Step 1: Compare and sort pairs (v[0], v[1]) and (v[2], v[3])
  if (v[0] <= v[1]) {
    min01 = v[0];
    max01 = v[1];
  } else {
    min01 = v[1];
    max01 = v[0];
    min_idx = 1;
  }

  if (v[2] <= v[3]) {
    min23 = v[2];
    max23 = v[3];
  } else {
    min23 = v[3];
    max23 = v[2];
  }

  // Step 2: Compare the minimums and maximums of the two pairs
  if (min01 <= min23) {
    v[0] = min01;
    v[1] = min23;
  } else {
    v[0] = min23;
    v[1] = min01;
    if (min_idx == 0)
      min_idx = 4; // The new minimum came from v[2]
  }

  if (max01 <= max23) {
    v[2] = max01;
    v[3] = max23;
    if (min_idx == 1)
      min_idx = 5; // The original v[1] is now at v[2]
  } else {
    v[2] = max23;
    v[3] = max01;
    if (min_idx == 1)
      min_idx = 3; // The original v[1] is now at v[3]
  }

  // Step 3: Final comparison to ensure the middle two elements are sorted
  if (v[1] <= v[2]) {
    // Array is fully sorted. Map temporary indices to final positions.
    if (min_idx == 4)
      min_idx = 1;
    if (min_idx == 5)
      return 2;
  } else {
    // Swap v[1] and v[2] to complete the sorting network
    double temp = v[1];
    v[1] = v[2];
    v[2] = temp;
    
    // Map temporary indices to final positions after the swap
    if (min_idx == 4)
      min_idx = 2;
    if (min_idx == 5)
      return 1;
  }

  return min_idx;
}