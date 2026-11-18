int calculate_income_tax(double amount,double *tax,double *rate)

{
  double *rate_local;
  double *tax_local;
  double amount_local;
  
  if ((amount < 0.0) || (DAT_00102008 < amount)) {
    if ((amount <= DAT_00102008) || (DAT_00102010 < amount)) {
      if (amount <= DAT_00102010) {
        return 1;
      }
      *rate = DAT_00102018;
    }
    else {
      *rate = DAT_00102020;
    }
  }
  else {
    *rate = DAT_00102028;
  }
  *tax = *rate * amount;
  return 0;
}