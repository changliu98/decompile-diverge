int func0(int actual_cost, int sale_amount)
{
  if (actual_cost > sale_amount)
    return actual_cost - sale_amount;
  else
    return -1;
}