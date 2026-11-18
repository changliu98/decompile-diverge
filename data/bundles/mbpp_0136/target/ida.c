double __cdecl func0(int units)
{
  int surcharge; // [rsp+Ch] [rbp-14h]
  double amount; // [rsp+10h] [rbp-10h]

  if ( units >= 50 )
  {
    if ( units > 100 )
    {
      if ( units > 200 )
      {
        amount = (double)(units - 200) * 8.449999999999999 + 818.5;
        surcharge = 75;
      }
      else
      {
        amount = (double)(units - 100) * 5.26 + 292.5;
        surcharge = 45;
      }
    }
    else
    {
      amount = (double)(units - 50) * 3.25 + 130.0;
      surcharge = 35;
    }
  }
  else
  {
    amount = (double)units * 2.6;
    surcharge = 25;
  }
  return amount + (double)surcharge;
}