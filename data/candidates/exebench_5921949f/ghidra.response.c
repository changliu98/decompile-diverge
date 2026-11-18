void factorial(double *fact)

{
  int count;
  double *fact_local;
  
  *fact = DAT_00102008;
  for (count = 0; count < 0x14; count = count + 1) {
    fact[count + 1] = (double)(count + 1) * fact[count];
  }
  return;
}