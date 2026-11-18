int get_profit(int actual_cost, int sale_amount)
{
  if (actual_cost > sale_amount)
    return actual_cost - sale_amount;
  else
    return -1;
}