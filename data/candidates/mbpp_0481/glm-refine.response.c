bool __cdecl func0(int *set, int n, int sum)
{
  // Base case: If the target sum is 0, the subset sum is satisfied
  if (sum == 0)
    return true;

  // Base case: If there are no elements left but the sum is not 0, it's impossible
  if (n == 0)
    return false;

  // If the current element is greater than the remaining sum, skip it
  if (set[n - 1] > sum)
    return func0(set, n - 1, sum);

  // Check if the sum can be achieved without the current element
  if (func0(set, n - 1, sum))
    return true;

  // Otherwise, check if the sum can be achieved by including the current element
  return func0(set, n - 1, sum - set[n - 1]);
}