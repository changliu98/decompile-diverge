int func0(int total_items, int group_size)
{
  // If N is less than K, return -1 as an error indicator
  if (total_items < group_size) {
    return -1;
  }
  else {
    // Calculate the sum of two triangular numbers:
    // First term: triangular number of (N - K + 1)
    // Second term: triangular number of (N - 2*K + 1)
    // Formula for triangular number T(n) = n * (n + 1) / 2
    return (((total_items - group_size) + 1) * ((total_items - group_size) + 2)) / 2 + ((total_items + group_size * -2 + 1) * (total_items + group_size * -2 + 2)) / 2;
  }
}