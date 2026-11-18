void __cdecl swapminusfloat(double *a, double *b)
{
  double temp = *a - *b;
  *b = temp + *b;
  *a = *b - temp;
}