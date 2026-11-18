int __cdecl func0(double *list1, int length)
{
  int sum; // [rsp+Ch] [rbp-14h]
  int i; // [rsp+10h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < length; ++i )
    sum = (int)((double)sum + round(list1[i]));
  return length * sum;
}