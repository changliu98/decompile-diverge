int octal_to_decimal(int n)
{
  int dec_value = 0;
  int base = 1;
  int last_digit = 0;
  while (n != 0)
  {
    last_digit = n % 10;
    n = n / 10;
    dec_value += last_digit * base;
    base = base * 8;
  }
  return dec_value;
}