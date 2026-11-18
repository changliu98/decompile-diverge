int __cdecl func0(int limit)
{
  int fact_0; // [rsp+0h] [rbp-20h]
  int sum_fact2; // [rsp+4h] [rbp-1Ch]
  int fact; // [rsp+8h] [rbp-18h]
  int sum_fact; // [rsp+Ch] [rbp-14h]
  int num; // [rsp+10h] [rbp-10h]
  int amicables_sum; // [rsp+14h] [rbp-Ch]

  if ( limit < 1 )
    return -1;
  amicables_sum = 0;
  for ( num = 2; num <= limit; ++num )
  {
    sum_fact = 0;
    for ( fact = 1; fact < num; ++fact )
    {
      if ( !(num % fact) )
        sum_fact += fact;
    }
    sum_fact2 = 0;
    for ( fact_0 = 1; fact_0 < sum_fact; ++fact_0 )
    {
      if ( !(sum_fact % fact_0) )
        sum_fact2 += fact_0;
    }
    if ( num == sum_fact2 && num != sum_fact )
      amicables_sum += num;
  }
  return amicables_sum;
}