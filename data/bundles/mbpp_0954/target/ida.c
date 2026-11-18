int __cdecl func0(int actual_cost, int sale_amount)
{
  if ( actual_cost <= sale_amount )
    return -1;
  else
    return actual_cost - sale_amount;
}