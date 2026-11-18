char *__cdecl func0(int *arr, int n, int p)
{
  int sum = 0;
  
  for (int i = 0; i < n; ++i)
    sum += arr[i];

  if (p != 1 || (sum % 2) != 0)
    return "EVEN";

  return (char *)&unk_2004; // Likely "ODD"
}