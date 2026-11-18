int __cdecl intwt(double N, double *W)
{
  int i;

  if (N >= 1.0)
  {
    // If N is 1.0 or greater, cast it to an integer and set W to 1.0
    i = (int)N;
    *W = 1.0;
  }
  else
  {
    // If N is less than 1.0, default i to 1 and set W to N
    i = 1;
    *W = N;
  }
  
  return i;
}