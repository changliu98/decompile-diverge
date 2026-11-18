double calculate_monthly_bill (int units)
{
 double monthly_bill, surcharge;
 if (units < 51)
 {
  monthly_bill = units * 2.60;
  surcharge = 25;
 }
 else if (units > 100)
 {
  if (units <= 200)
  {
   monthly_bill = 51 * 2.60 + (units - 51) * 5.20;
   surcharge = 35;
  }
  else
  {
   monthly_bill = 101 * 2.60 + (units - 101) * 8.40;
   surcharge = 75;
  }
 }
 else
 {
  monthly_bill = 51 * 2.60 + (units - 51) * 5.20;
  surcharge = 35;
 }
 double total_monthly_bill = monthly_bill + surcharge;
 return total_monthly_bill;
}