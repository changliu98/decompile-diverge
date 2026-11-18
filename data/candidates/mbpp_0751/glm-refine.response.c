bool __cdecl func0(int *arr, int n, int i)
{
  // Base case: If the current node has no children, it's a valid heap node.
  if (2 * i + 2 > n)
    return true;

  // Recursively check the left child (2 * i + 1)
  bool left_valid = false;
  if (arr[i] <= arr[2 * i + 1])
    left_valid = func0(arr, n, 2 * i + 1);

  // If the left subtree is invalid, the whole subtree is invalid.
  if (!left_valid)
    return false;

  // Check the right child (2 * i + 2), if it exists
  bool right_valid = true;
  if (2 * i + 2 != n)
  {
    right_valid = false;
    if (arr[i] <= arr[2 * i + 2])
      right_valid = func0(arr, n, 2 * i + 2);
  }

  return right_valid;
}