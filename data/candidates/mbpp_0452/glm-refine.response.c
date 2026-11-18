// Calculates the profit from a sale.
// Returns 0 if the sale amount is less than or equal to the actual cost (no profit or loss).
// Otherwise, returns the difference (profit).
int __cdecl calculate_profit(int actual_cost, int sale_amount)
{
  return (sale_amount > actual_cost) ? (sale_amount - actual_cost) : 0;
}