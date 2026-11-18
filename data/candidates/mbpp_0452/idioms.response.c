int func0(int actual_cost, int sale_amount)
{
  int profit = sale_amount - actual_cost;
  if ( profit > 0 )
    return profit;
  else
    return 0;
}