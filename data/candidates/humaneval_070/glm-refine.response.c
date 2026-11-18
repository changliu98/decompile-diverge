void __cdecl func0(int *lst, int size, int *out)
{
  int left, right, out_idx, i, j, temp;

  // 1. Sort the array in ascending order (using Selection Sort)
  for (i = 0; i < size - 1; ++i)
  {
    for (j = i + 1; j < size; ++j)
    {
      if (lst[i] > lst[j])
      {
        temp = lst[i];
        lst[i] = lst[j];
        lst[j] = temp;
      }
    }
  }

  // 2. Interleave elements from the ends towards the center 
  // (picking from the right first, then the left)
  left = 0;
  right = size - 1;
  out_idx = 0;
  
  while (left <= right)
  {
    if (left == right)
    {
      // If there's only one element left, pick it and move the left pointer
      // to break the loop condition.
      out[out_idx++] = lst[left++];
    }
    else
    {
      // Pick from the right side
      out[out_idx++] = lst[right--];
      
      // Pick from the left side
      out[out_idx++] = lst[left++];
    }
  }
}