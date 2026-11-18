double func0(int n) {
  double sum;
  int tax;
  if (n < 50) {
    sum = n * 2.6;
    tax = 25;
  } else if (n <= 100) {
    sum = 130 + (n - 50) * 3.25;
    tax = 35;
  } else if (n <= 200) {
    sum = 292.5 + (n - 100) * 5.26;
    tax = 45;
  } else {
    sum = 818.5 + (n - 200) * 8.45;
    tax = 75;
  }
  return sum + tax;
}