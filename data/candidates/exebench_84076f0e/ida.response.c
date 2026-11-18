int __cdecl calculate_income_tax(const double amount, double *tax, double *rate)
{
  if ( amount >= 0.0 && amount <= 1000.0 )
  {
    *rate = 0.25;
LABEL_10:
    *tax = *rate * amount;
    return 0;
  }
  if ( amount > 1000.0 && amount <= 5000.0 )
  {
    *rate = 0.3;
    goto LABEL_10;
  }
  if ( amount > 5000.0 )
  {
    *rate = 0.35;
    goto LABEL_10;
  }
  return 1;
}