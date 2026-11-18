int __cdecl int2arr(int *arr, int num)
{
  int i = 0;
  
  while (num != 0)
  {
    arr[i] = num % 10;
    num /= 10;
    i++;
  }
  
  return i;
}