char **__cdecl func0(char **arr1, int n1, char **arr2, int n2)
{
  int sum1 = 0;
  int sum2 = 0;

  // Calculate the total length of strings in arr1
  for (int i = 0; i < n1; ++i)
    sum1 += strlen(arr1[i]);

  // Calculate the total length of strings in arr2
  for (int i = 0; i < n2; ++i)
    sum2 += strlen(arr2[i]);

  // If sum1 is strictly less than sum2, return arr1
  if (sum1 < sum2)
    return arr1;

  // If sum1 is equal to sum2, return arr1
  if (sum1 <= sum2)
    return arr1;

  // If sum1 is greater than sum2, return arr2
  return arr2;
}