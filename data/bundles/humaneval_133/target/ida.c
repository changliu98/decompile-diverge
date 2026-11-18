int __cdecl func0(float *lst, int size)
{
  int v3; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int sum; // [rsp+10h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < size; ++i )
  {
    v3 = (int)ceil(lst[i]);
    sum += (int)ceil(lst[i]) * v3;
  }
  return sum;
}