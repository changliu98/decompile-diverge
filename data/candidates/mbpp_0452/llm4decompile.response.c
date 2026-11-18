int func0(int actual_cost, int sale_amount)
{
 int profit;

 if (sale_amount > actual_cost)
  profit = sale_amount - actual_cost;
 else
  profit = 0;

 return profit;
}