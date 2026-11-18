int calculate_income_tax(double amount, double *tax, double *rate)
{
  if (amount < 0 || amount > 1000)
    return 1;
  *rate = 0.25;
  *tax = amount * *rate;
  return 0;
}