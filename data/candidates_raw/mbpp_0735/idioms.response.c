int set_one_bit(int n)
{
  if (n == 1)
    return 1;
  else
    return n ^ set_middle_bits(n);
}