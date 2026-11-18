double round_to(double value, int digits)
{
  double n = pow(10,-digits);
  double rounded = (ceil(value/n)*n);
  return round(rounded * pow(10,digits)) / pow(10,digits);
}