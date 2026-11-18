void __cdecl func0(int *numbers, int size, int *result)
{
  int i; // [rsp+0h] [rbp-24h]
  int product; // [rsp+4h] [rbp-20h]
  int sum; // [rsp+8h] [rbp-1Ch]

  sum = 0;
  product = 1;
  for ( i = 0; i < size; ++i )
  {
    sum += numbers[i];
    product *= numbers[i];
  }
  *result = sum;
  result[1] = product;
}