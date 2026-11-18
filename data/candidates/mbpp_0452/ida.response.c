int __cdecl func0(int actual_cost, int sale_amount)
{
  if ( sale_amount <= actual_cost )
    return 0;
  else
    return sale_amount - actual_cost;
}