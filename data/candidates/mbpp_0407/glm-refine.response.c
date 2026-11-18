int __cdecl func0(int n)
{
  char nums[12]; // Buffer to hold the string representation of the number (max 10 digits + sign + null)
  char suffix[12]; // Buffer to hold the suffix being processed
  char swap_char;
  size_t i, j, k;
  size_t length, suffix_len;

  // Convert the integer to a string
  sprintf(nums, "%d", (unsigned int)n);
  length = strlen(nums);

  // Step 1: Find the first digit (from the right) that is smaller than the digit immediately after it
  for (i = length - 2; ; --i)
  {
    // If no such digit is found, the digits are in descending order,
    // meaning this is the largest possible permutation.
    if (i == (size_t)-1) // Equivalent to original `i < 0` check for signed underflow
      return 0;
    if (nums[i] < nums[i + 1])
      break;
  }

  // Step 2: Extract the suffix starting from the found digit
  strcpy(suffix, &nums[i]);
  suffix_len = strlen(suffix);

  // Step 3: Find the smallest digit in the suffix that is strictly greater than nums[i]
  // (The original code initializes `y` with `z[1]`, assuming the suffix is at least 2 chars long.
  // This is safe because if `i` was valid, `length - 2` ensures at least two elements exist.)
  swap_char = suffix[1];
  for (j = 1; j < suffix_len; ++j)
  {
    if (suffix[j] > suffix[0] && suffix[j] < swap_char)
      swap_char = suffix[j];
  }

  // Step 4: Remove the found `swap_char` from the suffix
  for (j = 0; j < suffix_len; ++j)
  {
    if (suffix[j] == swap_char)
    {
      // Shift characters left to overwrite the found character
      for (k = j; k < suffix_len - 1; ++k)
        suffix[k] = suffix[k + 1];
      
      suffix[suffix_len - 1] = '\0'; // Null-terminate the shifted string
      break;
    }
  }

  // Step 5: Sort the remaining characters of the suffix in ascending order
  qsort(suffix, strlen(suffix), sizeof(char), char_cmp);

  // Step 6: Place the `swap_char` at position `i` and append the sorted suffix
  nums[i] = swap_char;
  strcpy(&nums[i + 1], suffix);

  // Convert the resulting string back to an integer and return
  return atoi(nums);
}