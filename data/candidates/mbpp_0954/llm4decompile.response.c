int func0(int actual_cost, int sale_amount)
{
 int profit;

 if (actual_cost > sale_amount)
  profit = actual_cost - sale_amount;
 else
  profit = -1;

 return profit;
}