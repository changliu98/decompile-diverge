int calculate_income_tax(double income, double *tax, double *tax_rate) {
  if (income >= 0 && income <= 1000) {
    *tax_rate = 0.25;
  } else if (income > 1000 && income <= 5000) {
    *tax_rate = 0.30;
  } else if (income > 5000) {
    *tax_rate = 0.35;
  } else {
    return 1;
  }
  *tax = income * *tax_rate;
  return 0;
}