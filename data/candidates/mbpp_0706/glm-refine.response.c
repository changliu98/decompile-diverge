bool __cdecl func0(int *arr1, int m, int *arr2, int n)
{
  bool hashset[1000];
  int i;

  // Initialize the hashset to false
  memset(hashset, 0, sizeof(hashset));

  // Populate the hashset with elements from arr1
  for (i = 0; i < m; ++i)
    hashset[arr1[i]] = true;

  // Check if every element in arr2 exists in the hashset
  for (i = 0; i < n; ++i)
  {
    if (!hashset[arr2[i]])
      return false;
  }

  return true;
}