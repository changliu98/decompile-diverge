int __cdecl func0(int actual_cost, int sale_amount)
{
  // Returns the profit (actual_cost - sale_amount) if actual_cost > sale_amount.
  // Otherwise, returns -1.
  return (actual_cost > sale_amount) ? (actual_cost - sale_amount) : -1;
}