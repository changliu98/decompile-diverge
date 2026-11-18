int func0(int n)
{
 int n_digits;

 if (n < 0)
  n_digits = 0;
 else if (n <= 1)
  n_digits = 1;
 else
  n_digits = (int)floor(log10((double)n / 0.4152396310) + log10(2.0 * (double)n) / 0.693147180559945) + 1;

 return n_digits;
}