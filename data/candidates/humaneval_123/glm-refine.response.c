void __cdecl func0(int n, int *out, int *size)
{
  int *arr = out;
  int cap = 10;
  
  *size = 1;
  *out = 1;
  
  // Generate Collatz sequence, storing odd numbers
  while (n != 1)
  {
    if (n % 2 == 1)
    {
      if (*size >= cap)
      {
        cap *= 2;
        arr = (int *)realloc(arr, sizeof(int) * cap);
      }
      arr[(*size)++] = n;
      n = 3 * n + 1;
    }
    else
    {
      n /= 2;
    }
  }
  
  // Insertion sort on the collected odd numbers
  int sz = *size;
  for (int i = 1; i < sz; ++i)
  {
    int key = arr[i];
    int j = i - 1;
    
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}