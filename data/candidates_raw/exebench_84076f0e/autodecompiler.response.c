int calculate(double amount, double *tax, double *rate) {
 int result;
 if ((amount >= 0) && (amount <= 1000)) {
  *rate = 0.25;
 } else if ((amount > 1000) && (amount <= 5000)) {
  *rate = 0.30;
 } else if (amount > 5000) {
  *rate = 0.35;
 } else {
  result = 1;
  goto end;
 }
 *tax = amount * *rate;
 result = 0;
 end:
 return result;
}