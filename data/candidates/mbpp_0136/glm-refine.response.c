double __cdecl func0(int units)
{
  double amount;
  int surcharge;

  if (units > 200) {
    amount = (units - 200) * 8.45 + 818.5;
    surcharge = 75;
  } else if (units > 100) {
    amount = (units - 100) * 5.26 + 292.5;
    surcharge = 45;
  } else if (units >= 50) {
    amount = (units - 50) * 3.25 + 130.0;
    surcharge = 35;
  } else {
    amount = units * 2.6;
    surcharge = 25;
  }

  return amount + surcharge;
}