double func0(int n) {
  double result;
  result = pow((double)n, 3.0);
  result /= (6.0 * sqrt(2.0));
  result *= 100.0;
  result = round(result);
  result /= 100.0;
  return result;
}