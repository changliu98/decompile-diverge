
int calculate_income_tax(const double amount, double *tax, double *rate){
  if(amount >= 0 && amount <= 1000) {
    *rate = 0.25;
  } else if (amount > 1000 && amount <= 5000) {
    *rate = 0.30;
  } else if (amount > 5000) {
    *rate = 0.35;
  } else {
    return 1;
  }

  *tax = *rate * amount;
  return 0;
}
