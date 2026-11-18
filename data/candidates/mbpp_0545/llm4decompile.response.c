int func0(int n)
{
 int result;

 if (n == 1)
  result = 0;
 else {
  result = take_L_and_F_set_bits(n);
  result ^= n;
 }
 return result;
}