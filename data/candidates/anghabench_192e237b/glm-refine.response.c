double estLog(double N)
{
  double logN = 1.0;
  
  for (double x = 10.0; N > x; x *= 10.0)
    logN += 1.0;
    
  return logN;
}