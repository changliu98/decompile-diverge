double func0(int units)
{
  double amount = 0.0;
  int surcharge = 0;
  if (units < 50)
  {
    amount = (double) units * 2.60;
    surcharge = 25;
  }
  else if (units <= 100)
  {
    amount = (double)(units - 50) * 3.25 + 130.00;
    surcharge = 35;
  }
  else if (units <= 200)
  {
    amount = (double)(units - 100) * 5.26 + 292.50;
    surcharge = 45;
  }
  else
  {
    amount = (double)(units - 200) * 8.45 + 818.50;
    surcharge = 75;
  }
  return (amount + (double)surcharge);
}