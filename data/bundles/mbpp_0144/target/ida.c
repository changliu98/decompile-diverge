int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = n - 1; i >= 0; --i )
    sum += arr[i] * i - arr[i] * (n - 1 - i);
  return sum;
}