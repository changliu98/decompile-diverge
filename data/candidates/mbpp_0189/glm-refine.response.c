// Finds the smallest missing positive integer in the array.
// Implements the classic "First Missing Positive" algorithm using in-place
// marking (adding n to arr[(v-1) % n] to record that value v is present).
// Returns: the smallest positive integer in [1, n+1] not present in arr.
int __cdecl first_missing_positive(int *arr, int n)
{
  int i;            // generic loop index
  int found_one;    // flag: 1 if value 1 is present in arr
  __int64 mark_idx; // index to mark (kept 64-bit to match original)

  // Phase 1: Check whether 1 is present in the array.
  found_one = 0;
  for (i = 0; i < n; ++i)
  {
    if (arr[i] == 1)
    {
      found_one = 1;
      break;
    }
  }
  // If 1 is not present, it is trivially the smallest missing positive.
  if (!found_one)
    return 1;

  // Phase 2: Sanitize - replace out-of-range values (<=0 or >n) with 1.
  // This is safe because we already verified that 1 is present, so
  // overwriting with 1 does not introduce a "false" missing value.
  for (i = 0; i < n; ++i)
  {
    if (arr[i] <= 0 || arr[i] > n)
      arr[i] = 1;
  }

  // Phase 3: Mark - for each value v in [1, n], add n to arr[(v-1) % n].
  // After this loop, arr[i] > n iff value (i+1) was seen in the array.
  // The modulo handles the case where arr[i] has already been incremented
  // by a previous marking step (preserving the original value).
  for (i = 0; i < n; ++i)
  {
    mark_idx = (arr[i] - 1) % n;
    arr[mark_idx] += n;
  }

  // Phase 4: Scan - the first index i with arr[i] <= n means value (i+1)
  // was never marked, so (i+1) is the smallest missing positive.
  for (i = 0; i < n; ++i)
  {
    if (arr[i] <= n)
      return i + 1;
  }

  // All values 1..n are present, so the answer is n+1.
  return n + 1;
}