bool __cdecl func0(int *q, int size, int w)
{
  int i;
  int sum = 0;
  int half_size = size / 2;

  // Iterate through the first half of the array
  for (i = 0; i < half_size; ++i)
  {
    int mirror_idx = size - 1 - i;

    // If elements don't match their mirror counterpart, it's not a palindrome
    if (q[i] != q[mirror_idx])
      return false;

    // Add both mirrored elements to the sum
    sum += q[i] + q[mirror_idx];
  }

  // If the array has an odd number of elements, add the middle element
  if (size % 2 == 1)
    sum += q[half_size];

  // Check if the total sum is within the allowed limit 'w'
  return sum <= w;
}