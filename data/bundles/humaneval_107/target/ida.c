int *__cdecl func0(int n)
{
  int number; // [rsp+10h] [rbp-20h]
  int reversed; // [rsp+18h] [rbp-18h]
  int i; // [rsp+1Ch] [rbp-14h]
  int *counts; // [rsp+20h] [rbp-10h]

  counts = (int *)malloc(8uLL);
  *counts = 0;
  counts[1] = 0;
  for ( i = 1; i <= n; ++i )
  {
    reversed = 0;
    for ( number = i; number; number /= 10 )
      reversed = number % 10 + 10 * reversed;
    if ( i == reversed )
    {
      if ( i % 2 )
        ++counts[1];
      else
        ++*counts;
    }
  }
  return counts;
}