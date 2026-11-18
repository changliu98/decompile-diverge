int ireduce(unsigned long long in_num, unsigned long long in_den, unsigned long long max_num, unsigned long long max_den, unsigned long long *out_num, unsigned long long *out_den)
{
  unsigned long long num1 = 0;
  unsigned long long den1 = 0;
  unsigned long long num0 = 1;
  unsigned long long den0 = 1;
  unsigned long long num;
  unsigned long long den;
  unsigned long long tmp;
  unsigned long long tmp2;
  while (num1 <= max_num && den1 <= max_den) {
    if (in_den == 0)
      break;
    den = in_den;
    tmp = in_num / in_den;
    in_den = in_num % in_den;
    in_num = den;
    num = num1 * tmp + num0;
    num0 = num1;
    num1 = num;
    den = den1 * tmp + den0;
    den0 = den1;
    den1 = den;
  }
  num = num0;
  den = den0;
  *out_num = num;
  *out_den = den;
  return 0;
}